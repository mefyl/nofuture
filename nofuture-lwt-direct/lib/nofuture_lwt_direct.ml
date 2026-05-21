include Nofuture_lwt_direct_intf

module Blocking = struct
  type 'a t = 'a

  let bind v ~f = f v
  let map v ~f = f v
  let return v = v
  let all v = v
  let catch f catch = try f () with exn -> catch exn
  let yield () = Lwt_direct.yield ()
  let both left right = (left, right)
  let join v = v
  let ignore_m _ = ()

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

  let run ?name:_ f =
    Lwt_direct.await
    @@ Lwt_switch.with_switch
    @@ fun switch -> Lwt_direct.spawn @@ fun () -> f switch
end

module Background = struct
  type 'a t = 'a Lwt.t

  let make () =
    let background, wake = Lwt.wait () in
    (background, Lwt.wakeup_later wake)
end

let defer switch f =
  let res = Lwt_direct.spawn f in
  let () = Lwt_switch.add_hook (Some switch) (fun () -> Lwt.(res >|= ignore)) in
  res

let await = Lwt_direct.await

module Mutex = struct
  type t = Lwt_mutex.t

  let make () = Lwt_mutex.create ()

  let use mutex f =
    Lwt_direct.await
    @@ Lwt_mutex.with_lock mutex
    @@ fun () -> Lwt_direct.spawn f
end

module Condition = struct
  type t = unit Lwt_condition.t

  let await ?mutex condition =
    Lwt_direct.await @@ Lwt_condition.wait ?mutex condition

  let broadcast condition = Lwt_condition.broadcast condition ()
  let make () = Lwt_condition.create ()
end

module In_channel = struct
  type t = {
    close : unit -> unit;
    mutable current : (int * string) option;
    stream : string Lwt_stream.t;
  }

  let close { close; _ } = close ()

  let empty =
    { close = (fun () -> ()); current = None; stream = Lwt_stream.of_list [] }

  let of_string current =
    {
      close = (fun () -> ());
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
      Some current.[idx]
    | channel -> (
      match Lwt_direct.await (Lwt_stream.get channel.stream) with
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
        String.sub current idx (String.length current - idx)
      | None -> (
        match Lwt_direct.await (Lwt_stream.get channel.stream) with
        | None -> ""
        | Some chunk -> chunk))
    | Some size ->
      let chunk = read channel in
      let length = String.length chunk in
      if length = 0 || length = size then chunk
      else if length > size then
        let () = channel.current <- Some (size, chunk) in
        String.sub chunk 0 size
      else
        let next = read ~size:(size - length) channel in
        chunk ^ next

  let read_all channel =
    let chunks = Lwt_direct.await @@ Lwt_stream.to_list channel.stream in
    let chunks =
      match channel.current with
      | None -> chunks
      | Some (idx, current) ->
        String.sub current idx (String.length current - idx) :: chunks
    in
    String.concat "" chunks

  let of_stream ?(close = fun () -> ()) stream =
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
