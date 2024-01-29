open Async

module Blocking = struct
  type 'a t = 'a Deferred.t

  let bind = Deferred.bind
  let map = Deferred.map
  let return = Deferred.return

  let catch f catch =
    Monitor.try_with f >>= function Ok v -> return v | Error exn -> catch exn

  let both = Deferred.both
  let all = Deferred.all
  let yield = Deferred.return

  module Syntax = struct
    let ( let* ) v f = bind v ~f
    let ( let+ ) v f = map v ~f
    let ( and* ) = both
    let ( and+ ) = both
  end

  include Syntax
end

include Blocking

module Scope = struct
  type t = Monitor.t

  let run ?name f =
    let monitor = Monitor.create ?name () in
    let () = Monitor.detach monitor in
    let result = within' ~monitor (fun () -> f monitor) in
    result
end

module Background = struct
  type 'a t = 'a Deferred.t

  let make () =
    let ivar = ref None in
    let background = Deferred.create (fun v -> ivar := Some v) in
    let resolve =
      match !ivar with
      | None -> failwith "unreachable"
      | Some ivar -> Ivar.fill ivar
    in
    (background, resolve)
end

let defer _monitor f = f ()
let await deferred = deferred

module In_channel = struct
  type t =
    | Empty
    | String of {
        mutable position : int;
        content : string;
      }
    | Reader of Reader.t

  let of_reader reader = Reader reader
  let close = function Reader reader -> Reader.close reader | _ -> return ()
  let empty = Empty
  let of_string content = String { position = 0; content }

  let read_char = function
    | Empty -> return None
    | Reader reader -> (
      Reader.read_char reader >>| function `Ok c -> Some c | `Eof -> None)
    | String channel ->
      if channel.position = String.length channel.content then return None
      else
        let () = channel.position <- channel.position + 1 in
        return (Some channel.content.[channel.position - 1])

  let read ?size = function
    | Empty -> return ""
    | Reader reader -> (
      let size = match size with None -> 4096 | Some size -> size in
      let buffer = Bytes.create size in
      Reader.read reader buffer >>| function
      | `Ok length -> Bytes.sub_string buffer 0 length
      | `Eof -> "")
    | String ({ position = 0; content } as channel)
      when match size with
           | None -> true
           | Some size -> String.length content <= size ->
      let () = channel.position <- String.length content in
      return content
    | String ({ position; content } as channel) ->
      let length =
        let length = String.length channel.content in
        match size with None -> length | Some size -> min size length
      in
      let () = channel.position <- length in
      return (String.sub content position (length - position))

  let read_all = function
    | Empty -> return ""
    | Reader reader ->
      let buffer = Bytes.create 4096
      and result = Buffer.create 4096 in
      let rec read () =
        Reader.read reader buffer >>= function
        | `Eof ->
          Buffer.to_bytes result |> Bytes.unsafe_to_string |> Deferred.return
        | `Ok length ->
          let () = Buffer.add_subbytes result buffer 0 length in
          read ()
      in
      read ()
    | String _ as channel -> read channel
end

module Out_channel = struct
  type t = Writer.t

  let close channel = Writer.close channel
  let write channel string = return (Writer.write channel string)
end

module Mutex = struct
  type t = {
    mutable locked : bool;
    waiting : unit Ivar.t Queue.t;
  }

  let make () = { locked = false; waiting = Queue.create () }

  let lock mutex =
    if mutex.locked then
      Deferred.create (fun ivar -> Queue.add ivar mutex.waiting)
    else
      let () = mutex.locked <- true in
      Deferred.unit

  let unlock mutex =
    if mutex.locked then
      match Queue.take_opt mutex.waiting with
      | None -> mutex.locked <- false
      | Some ivar -> Ivar.fill ivar ()

  let use mutex f =
    let* () = lock mutex in
    Monitor.protect ~finally:(fun () -> return (unlock mutex)) f
end

module Condition = struct
  type t = unit Condition.t

  let await ?mutex condition =
    match mutex with
    | None -> Condition.wait condition
    | Some mutex ->
      let () = Mutex.unlock mutex in
      Monitor.protect ~finally:(fun () -> Mutex.lock mutex) @@ fun () ->
      Condition.wait condition

  let broadcast condition = Condition.broadcast condition ()
  let make () = Condition.create ()
end
