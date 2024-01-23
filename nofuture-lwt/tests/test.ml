include Nofuture_tests.Make (Nofuture_lwt)

let () =
  let run f () = Lwt_main.run @@ f () in
  check "Nofuture Lwt" run
