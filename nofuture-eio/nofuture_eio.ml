include Nofuture_eio_intf

module Blocking = struct
  type 'a t = 'a
end

include Blocking

let bind v ~f = f v
let map v ~f = f v
let return v = v
let catch f handler = try f () with exn -> handler exn

module Scope = struct
  type t = Eio.Switch.t

  let run ?name f = Eio.Switch.run ?name f
end

module Deferred = struct
  type 'a t = 'a Eio.Promise.or_exn

  let make () =
    let deferred, wake = Eio.Promise.create () in
    (deferred, Eio.Promise.resolve_ok wake)
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

    let read_methods = [ Flow.String (fun () -> raise End_of_file) ]
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
          | { string = ""; _ } -> raise End_of_file
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

  module Bytes_source = struct
    type t = {
      bytes : Bytes.t;
      mutable offset : int;
    }

    let read_methods =
      [
        Flow.Bytes
          (function
          | { bytes; _ } when Bytes.length bytes = 0 -> raise End_of_file
          | { bytes; offset = 0 } as t ->
            let () = t.offset <- Bytes.length bytes in
            Some bytes
          | _ -> None);
      ]

    let single_read t dst =
      let len = Bytes.length t.bytes in
      if t.offset = len then raise End_of_file;
      let len = min (Cstruct.length dst) (len - t.offset) in
      Cstruct.blit_from_bytes t.bytes t.offset dst 0 len;
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

  let of_bytes bytes =
    Eio.Resource.T
      ( { Bytes_source.bytes; offset = 0 },
        Eio.Resource.handler
          [
            H (Eio.Flow.Pi.Source, (module Bytes_source));
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

  let read_string (Eio.Resource.T (t, ops)) =
    let module Source = (val Eio.Resource.get ops Eio.Flow.Pi.Source) in
    let optimization = function
      | Flow.String f -> f t
      | Flow.Bytes f -> Option.map Bytes.to_string (f t)
      | _ -> None
    in
    match List.find_map optimization Source.read_methods with
    | Some string -> string
    | None ->
      let buffer = Cstruct.create 4096 in
      let len = Source.single_read t buffer in
      Cstruct.to_string ~len buffer

  let read channel =
    let buffer, len = _read channel in
    Cstruct.to_bytes ~len buffer

  let read_all_string = Eio.Flow.read_all
  let read_all channel = Bytes.of_string @@ read_all_string channel
end

module Out_channel = struct
  type t = [ Eio.Flow.sink_ty | `Close ] Eio.Resource.t

  let close = Eio.Flow.close
  let write_string t string = Eio.Flow.write t [ Cstruct.of_string string ]
  let write t bytes = Eio.Flow.write t [ Cstruct.of_bytes bytes ]
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
