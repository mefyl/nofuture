module Nofuture_eio = struct
  include Nofuture_eio

  let mono_clock = ref None

  let my_traceln =
    {
      Eio.Debug.traceln =
        (fun ?__POS__:_ fmt ->
          Format.kdprintf ignore ("[custom-trace] " ^^ fmt ^^ "@."));
    }

  let run f =
    Eio_mock.Backend.run_full @@ fun env ->
    let debug = Eio.Stdenv.debug env in
    Eio.Fiber.with_binding debug#traceln my_traceln @@ fun () ->
    let () = mono_clock := Some (Eio.Stdenv.mono_clock env) in
    f ()

  let mono_clock () =
    match !mono_clock with
    | Some clock -> clock
    | None -> failwith "test setup error"

  let sleep span = Eio.Time.Mono.sleep (mono_clock ()) span
end

module Nofuture_lwt = struct
  include Nofuture_lwt

  let run f = Lwt_main.run @@ f ()
  let sleep span = Lwt_unix.sleep span
end

include Nofuture_eio
