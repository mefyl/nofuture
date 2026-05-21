include Nofuture_lwt_direct

module In_channel = struct
  include Nofuture_lwt_unix.In_channel

  let close t = Lwt_direct.await @@ close t
  let read_char t = Lwt_direct.await @@ read_char t
  let read ?size t = Lwt_direct.await @@ read ?size t

  let read_all t =
    let buffer = Buffer.create 4096 in
    let rec read () =
      match Lwt_direct.await (Lwt_io.read t) with
      | "" -> Buffer.to_bytes buffer |> Bytes.unsafe_to_string
      | chunk ->
        let () = Buffer.add_string buffer chunk in
        read ()
    in
    read ()

  let of_stream ?close t =
    let close =
      match close with
      | None -> None
      | Some close -> Some (fun () -> close () |> Lwt.return)
    in
    of_stream ?close t
end

module Out_channel = struct
  type t = Lwt_io.output_channel

  let close t = Lwt_direct.await @@ Lwt_io.close t
  let write t string = Lwt_direct.await @@ Lwt_io.write t string
end

let sleep duration = Lwt_direct.await @@ Lwt_unix.sleep duration
