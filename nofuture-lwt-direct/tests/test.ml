include Nofuture_tests.Make (Nofuture_lwt_direct)

let () =
  let run f () = Lwt_main.run @@ Lwt_direct.spawn f in
  check "Nofuture Lwt direct" run
