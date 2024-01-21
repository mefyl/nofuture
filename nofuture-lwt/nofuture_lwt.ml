module Blocking = struct
  type 'a t = 'a Lwt.t

  let bind v ~f = Lwt.bind v f
  let map v ~f = Lwt.map f v
  let return = Lwt.return
  let catch = Lwt.catch
  let both = Lwt.both
  let all = Lwt.all
end

include Blocking

module Scope = struct
  type t = Lwt_switch.t

  let run ?name:_ f = Lwt_switch.with_switch f
end

module Deferred = struct
  type 'a t = 'a Lwt.t

  let make () =
    let deferred, wake = Lwt.wait () in
    (deferred, Lwt.wakeup_later wake)
end

let defer _ f = f ()
let await p = p

module In_channel = struct
  type t = Lwt_io.input_channel

  let close = Lwt_io.close
  let empty = Lwt_io.of_bytes ~mode:Input @@ Lwt_bytes.create 0
  let of_bytes bytes = Lwt_io.of_bytes ~mode:Input @@ Lwt_bytes.of_bytes bytes

  let of_string string =
    Lwt_io.of_bytes ~mode:Input @@ Lwt_bytes.of_string string

  let read_char = Lwt_io.read_char_opt
  let read_string channel = Lwt_io.read ~count:4096 channel
  let read channel = Lwt.map Bytes.of_string @@ read_string channel

  let read_all channel =
    let buffer = Buffer.create 512 in
    let rec read () =
      Lwt.bind (Lwt_io.read channel) (function
        | "" -> Lwt.return (Buffer.to_bytes buffer)
        | chunk ->
          let () = Buffer.add_string buffer chunk in
          read ())
    in
    read ()

  let read_all_string channel = Lwt.map Bytes.to_string @@ read_all channel
end

module Out_channel = struct
  type t = Lwt_io.output_channel

  let close = Lwt_io.close
  let write_string = Lwt_io.write
  let write t bytes = Lwt_io.write t @@ Bytes.to_string bytes
end

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
