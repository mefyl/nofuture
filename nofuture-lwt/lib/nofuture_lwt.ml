include Nofuture_lwt_intf

module Blocking = struct
  type 'a t = 'a Lwt.t

  let bind v ~f = Lwt.bind v f
  let map v ~f = Lwt.map f v
  let return = Lwt.return
  let catch = Lwt.catch
  let both = Lwt.both
  let all = Lwt.all
  let yield = Lwt.pause
  let join t = bind t ~f:(fun t' -> t')
  let ignore_m t = map t ~f:(fun _ -> ())

  let rec all_unit = function
    | [] -> return ()
    | t :: ts -> bind t ~f:(fun () -> all_unit ts)

  module Monad_infix = struct
    let ( >>= ) v f = bind v ~f
    let ( let* ) = ( >>= )
    let ( >>| ) v f = map v ~f
    let ( let+ ) = ( >>| )
    let ( and* ) = both
    let ( and+ ) = both
  end

  include Monad_infix

  module Let_syntax = struct
    let return = return

    include Monad_infix

    module Let_syntax = struct
      let return = return
      let bind = bind
      let map = map
      let both = both

      module Open_on_rhs = struct end
    end
  end
end

include Blocking

module Scope = struct
  type t = Lwt_switch.t

  let run ?name:_ f = Lwt_switch.with_switch f
end

module Background = struct
  type 'a t = 'a Lwt.t

  let make () =
    let background, wake = Lwt.wait () in
    (background, Lwt.wakeup_later wake)
end

let defer switch f =
  let res = f () in
  let () = Lwt_switch.add_hook (Some switch) (fun () -> Lwt.(res >|= ignore)) in
  res

let await p = p

module Mutex = struct
  type t = Lwt_mutex.t

  let make () = Lwt_mutex.create ()
  let use mutex f = Lwt_mutex.with_lock mutex f
end

module Condition = struct
  type t = unit Lwt_condition.t

  let await ?mutex condition = Lwt_condition.wait ?mutex condition
  let broadcast condition = Lwt_condition.broadcast condition ()
  let make () = Lwt_condition.create ()
end

module In_channel = struct
  type t = {
    close : unit -> unit Lwt.t;
    mutable current : (int * string) option;
    stream : string Lwt_stream.t;
  }

  let close { close; _ } = close ()

  let empty =
    {
      close = (fun () -> Lwt.return_unit);
      current = None;
      stream = Lwt_stream.of_list [];
    }

  let of_string current =
    {
      close = (fun () -> Lwt.return_unit);
      current = Some (0, current);
      stream = Lwt_stream.of_list [];
    }

  let read_char = function
    | { current = Some (idx, current); _ } as channel ->
      let () =
        channel.current <-
          (if idx + 1 < String.length current then Some (idx + 1, current)
           else None)
      in
      Some current.[idx] |> Lwt.return
    | channel -> (
      Lwt_stream.get channel.stream >>| function
      | None -> None
      | Some s when String.length s = 1 -> Some s.[0]
      | Some s ->
        let () = channel.current <- Some (1, s) in
        Some s.[0])

  let rec read ?size channel =
    match size with
    | None -> (
      match channel.current with
      | Some (idx, current) ->
        let () = channel.current <- None in
        String.sub current idx (String.length current - idx) |> Lwt.return
      | None -> (
        Lwt_stream.get channel.stream >>| function
        | None -> ""
        | Some chunk -> chunk))
    | Some size ->
      let open Lwt.Syntax in
      let* chunk = read channel in
      let length = String.length chunk in
      if length = 0 || length = size then Lwt.return chunk
      else if length > size then
        let () = channel.current <- Some (size, chunk) in
        Lwt.return (String.sub chunk 0 size)
      else
        let+ next = read ~size:(size - length) channel in
        chunk ^ next

  let read_all channel =
    let open Lwt.Syntax in
    let+ chunks = Lwt_stream.to_list channel.stream in
    let chunks =
      match channel.current with
      | None -> chunks
      | Some (idx, current) ->
        String.sub current idx (String.length current - idx) :: chunks
    in
    String.concat "" chunks

  let of_stream ?(close = fun () -> Lwt.return_unit) stream =
    { close; current = None; stream }

  let to_stream { current; stream; _ } =
    match current with
    | Some (idx, current) ->
      Lwt_stream.append
        (Lwt_stream.return
           (String.sub current idx @@ (String.length current - idx)))
        stream
    | None -> stream
end

module Out_channel = struct
  type t = |

  let close = function (_ : t) -> .
  let write = function (_ : t) -> .
end
