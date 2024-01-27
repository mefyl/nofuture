include Nofuture_tests.Make (Nofuture_async)

let () =
  let run f () = Async.Thread_safe.block_on_async_exn f in
  check "Nofuture Async" run
