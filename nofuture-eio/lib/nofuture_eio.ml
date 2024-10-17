include Nofuture_eio_intf

module Blocking = struct
  type 'a t = 'a

  let bind v ~f = f v
  let map v ~f = f v
  let return v = v
  let catch f handler = try f () with exn -> handler exn
  let both a b = (a, b)
  let all list = list
  let yield = Eio.Fiber.yield
  let join v = v
  let ignore_m = ignore
  let all_unit = ignore

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
  type t = Eio.Switch.t

  let run ?name f = Eio.Switch.run ?name f
end

module Background = struct
  type 'a t = 'a Eio.Promise.or_exn

  let make () =
    let background, wake = Eio.Promise.create () in
    (background, Eio.Promise.resolve_ok wake)
end

let defer sw f = Eio.Fiber.fork_promise ~sw f

let await p =
  match Eio.Promise.await p with
  | Result.Ok ok -> ok
  | Result.Error exn -> raise exn

module In_channel = struct
  type t = [ Eio.Flow.source_ty | `Close ] Eio.Resource.t

  let close = Eio.Flow.close

  module Empty_source = struct
    type t = unit

    let read_methods = [ Flow.String (fun () -> Some "") ]
    let single_read _ _ = raise End_of_file
  end

  let empty =
    Eio.Resource.T
      ( (),
        Eio.Resource.handler
          [
            H (Eio.Flow.Pi.Source, (module Empty_source));
            H (Eio.Resource.Close, fun _ -> ());
          ] )

  module String_source = struct
    type t = {
      string : string;
      mutable offset : int;
    }

    let read_methods =
      [
        Flow.String
          (function
          | { string; offset = 0 } as t ->
            let () = t.offset <- String.length string in
            Some string
          | _ -> None);
      ]

    let single_read t dst =
      if t.offset = String.length t.string then raise End_of_file;
      let len = min (Cstruct.length dst) (String.length t.string - t.offset) in
      Cstruct.blit_from_string t.string t.offset dst 0 len;
      t.offset <- t.offset + len;
      len
  end

  let of_string string =
    Eio.Resource.T
      ( { String_source.string; offset = 0 },
        Eio.Resource.handler
          [
            H (Eio.Flow.Pi.Source, (module String_source));
            H (Eio.Resource.Close, fun _ -> ());
          ] )

  let read_char channel =
    let buffer = Cstruct.create 1 in
    match Eio.Flow.single_read channel buffer with
    | (exception End_of_file) | 0 -> None
    | _ -> Some (Cstruct.get buffer 0)

  let _read channel =
    let buffer = Cstruct.create 4096 in
    let len = Eio.Flow.single_read channel buffer in
    (buffer, len)

  let read ?size (Eio.Resource.T (t, ops)) =
    let module Source = (val Eio.Resource.get ops Eio.Flow.Pi.Source) in
    let optimization = function Flow.String f -> f t | _ -> None in
    match List.find_map optimization Source.read_methods with
    | Some string
      when match size with
           | None -> true
           | Some size -> String.length string <= size ->
      string
    | _ ->
      let size = match size with None -> 4096 | Some size -> size in
      let buffer = Cstruct.create size in
      let len = Source.single_read t buffer in
      Cstruct.to_string ~len buffer

  let read_all = Eio.Flow.read_all
end

module Out_channel = struct
  type t = [ Eio.Flow.sink_ty | `Close ] Eio.Resource.t

  let close = Eio.Flow.close
  let write t string = Eio.Flow.write t [ Cstruct.of_string string ]
end

module Mutex = struct
  type t = Eio.Mutex.t

  let make () = Eio.Mutex.create ()
  let use mutex f = Eio.Mutex.use_ro mutex f
end

module Condition = struct
  type t = Eio.Condition.t

  let await ?mutex condition =
    match mutex with
    | None -> Eio.Condition.await_no_mutex condition
    | Some mutex -> Eio.Condition.await condition mutex

  let broadcast condition = Eio.Condition.broadcast condition
  let make () = Eio.Condition.create ()
end
