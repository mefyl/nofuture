include Nofuture_tests.Make (Nofuture_eio)

let () =
  let run f () = Eio_mock.Backend.run_full @@ fun _ -> f () in
  check "Nofuture Eio" run
