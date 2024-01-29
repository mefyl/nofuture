include Nofuture_tests.Make (Nofuture_async)
open Nofuture_async
open Async

(* let () = *)
(*   let main () = *)
(*     let monitor = Monitor.create ~name:"XXX" () in *)
(*     let+ () = *)
(*       within' ~monitor @@ fun () -> *)
(*       let+ () = *)
(*         let+ () = yield () in *)
(*         Format.eprintf "raise@."; *)
(*         raise End_of_file *)
(*       and+ () = *)
(*         let* () = yield () in *)
(*         Format.eprintf "ping@."; *)
(*         let* () = yield () in *)
(*         Format.eprintf "ping@."; *)
(*         let* () = yield () in *)
(*         Format.eprintf "ping@."; *)
(*         let* () = yield () in *)
(*         Format.eprintf "ping@."; *)
(*         let+ () = yield () in *)
(*         Format.eprintf "done@." *)
(*       in *)
(*       () *)
(*     in *)
(*     Format.eprintf "out of monitor@." *)
(*   in *)
(*   Async.Thread_safe.block_on_async_exn main *)

let () =
  let main () =
    Monitor.handle_errors ~name:"XXX"
      (fun () ->
        let+ () =
          let+ () = yield () in
          Format.eprintf "raise@.";
          raise End_of_file
        and+ () =
          let* () = yield () in
          Format.eprintf "ping@.";
          let* () = yield () in
          Format.eprintf "ping@.";
          let* () = yield () in
          Format.eprintf "ping@.";
          let* () = yield () in
          Format.eprintf "ping@.";
          let+ () = yield () in
          raise End_of_file
        in
        ())
      (fun _ -> Format.eprintf "EXN@.")
  in
  Async.Thread_safe.block_on_async_exn main

(* let () = *)
(*   let main () = *)
(*     try_with (fun () -> *)
(*         let monitor = Monitor.create () in *)
(*         within' ~monitor @@ fun () -> *)
(*         let+ () = *)
(*           let+ () = yield () in *)
(*           raise End_of_file *)
(*         and+ () = *)
(*           let* () = yield () in *)
(*           Format.eprintf "ping@."; *)
(*           let* () = yield () in *)
(*           Format.eprintf "ping@."; *)
(*           let* () = yield () in *)
(*           Format.eprintf "ping@."; *)
(*           let* () = yield () in *)
(*           Format.eprintf "ping@."; *)
(*           let+ () = yield () in *)
(*           Format.eprintf "inside@." *)
(*         in *)
(*         ()) *)
(*     >>| function *)
(*     | Result.Ok () -> () *)
(*     | Error _exn -> Format.eprintf "caught@." *)
(*   in *)
(*   let _ = Async.Thread_safe.block_on_async main in *)
(*   Format.eprintf "/main@." *)

(* let () = *)
(*   let run f () = Async.Thread_safe.block_on_async_exn f in *)
(*   check "Nofuture Async" run *)
