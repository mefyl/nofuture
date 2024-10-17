include Nofuture_lwt

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

  let of_stream ?close stream =
    let open Lwt.Infix in
    let pending = ref None in
    Lwt_io.make ?close ~mode:Lwt_io.input @@ fun buffer pos size ->
    match !pending with
    | Some (chunk, chunk_pos) ->
      let length = String.length chunk - chunk_pos in
      if length <= size then
        let () = Lwt_bytes.blit_from_string chunk chunk_pos buffer pos length
        and () = pending := None in
        Lwt.return length
      else
        let () = Lwt_bytes.blit_from_string chunk chunk_pos buffer pos size
        and () = pending := Some (chunk, chunk_pos + size) in
        Lwt.return size
    | None -> (
      Lwt_stream.get stream >|= function
      | Some chunk ->
        let length = String.length chunk in
        if length <= size then
          let () = Lwt_bytes.blit_from_string chunk 0 buffer pos length in
          length
        else
          let () = Lwt_bytes.blit_from_string chunk 0 buffer pos size
          and () = pending := Some (chunk, size) in
          size
      | None -> 0)

  let to_stream channel =
    let open Lwt.Infix in
    Lwt_stream.from @@ fun () ->
    Lwt_io.read channel >|= function "" -> None | chunk -> Some chunk
end

module Out_channel = struct
  type t = Lwt_io.output_channel

  let close = Lwt_io.close
  let write = Lwt_io.write
end

let sleep = Lwt_unix.sleep
