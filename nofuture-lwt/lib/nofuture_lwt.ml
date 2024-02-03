module Blocking = struct
  type 'a t = 'a Lwt.t

  let bind v ~f = Lwt.bind v f
  let map v ~f = Lwt.map f v
  let return = Lwt.return
  let catch = Lwt.catch
  let both = Lwt.both
  let all = Lwt.all
  let yield = Lwt.pause

  module Syntax = struct
    let ( >>= ) v f = bind v ~f
    let ( let* ) = ( >>= )
    let ( >>| ) v f = map v ~f
    let ( let+ ) = ( >>| )
    let ( and* ) = both
    let ( and+ ) = both
  end

  include Syntax
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

module In_channel = struct
  type t = Lwt_io.input_channel

  let close = Lwt_io.close
  let empty = Lwt_io.of_bytes ~mode:Input @@ Lwt_bytes.create 0

  let of_string string =
    Lwt_io.of_bytes ~mode:Input @@ Lwt_bytes.of_string string

  let read_char = Lwt_io.read_char_opt

  let read ?size channel =
    let count = match size with None -> 4096 | Some size -> size in
    Lwt_io.read ~count channel

  let read_all channel =
    let buffer = Buffer.create 4096 in
    let rec read () =
      Lwt.bind (Lwt_io.read channel) (function
        | "" -> Buffer.to_bytes buffer |> Bytes.unsafe_to_string |> Lwt.return
        | chunk ->
          let () = Buffer.add_string buffer chunk in
          read ())
    in
    read ()

  let read_until channel stop =
    let buffer = Buffer.create 128 in
    let rec loop () =
      Lwt.try_bind
        (fun () -> read_char channel)
        (function
          | None -> Lwt.return (Buffer.contents buffer)
          | Some char when Char.equal char stop ->
            Lwt.return (Buffer.contents buffer)
          | Some char ->
            let () = Buffer.add_char buffer char in
            loop ())
        (function
          | End_of_file -> Lwt.return (Buffer.contents buffer)
          | exn -> Lwt.fail exn)
    in
    loop ()
end

module Out_channel = struct
  type t = Lwt_io.output_channel

  let close = Lwt_io.close
  let write = Lwt_io.write
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
