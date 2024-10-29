module Make (Future : Nofuture.S) : sig
  val check : string -> ((unit -> unit Future.t) -> unit -> unit) -> unit
end = struct
  open Future

  module Blocking = struct
    let sequence () =
      let* () = Future.yield () in
      let+ () = Future.yield () in
      ()

    let concurrent () =
      let i = ref 0 in
      let check ~here expected =
        match List.find_opt (( = ) !i) expected with
        | Some _ -> i := !i + 1
        | None -> Alcotest.failf ~here "unexpected counter value %d" !i
      in
      let+ () =
        let () = check ~here:[%here] [ 0 ] in
        let+ () = Future.yield () in
        check ~here:[%here] [ 1; 2 ]
      and+ () =
        let () = check ~here:[%here] [ 1; 2 ] in
        let+ () = Future.yield () in
        check ~here:[%here] [ 3 ]
      in
      ()
  end

  module Background = struct
    let concurrent () =
      let i = ref 0 in
      let check ~here expected =
        let () = Alcotest.(check ~here int) "counter" expected !i in
        i := !i + 1
      in
      Scope.run @@ fun scope ->
      let a =
        defer scope @@ fun () ->
        let () = check ~here:[%here] 0 in
        let* () = Future.yield () in
        let+ () = Future.yield () in
        check ~here:[%here] 2
      and b =
        defer scope @@ fun () ->
        let () = check ~here:[%here] 1 in
        let* () = Future.yield () in
        let+ () = Future.yield () in
        check ~here:[%here] 3
      in
      let+ () = await a
      and+ () = await b in
      ()
  end

  module Scope = struct
    let join () =
      let i = ref 0 in
      let check ~here expected =
        let () = Alcotest.(check ~here int) "counter" expected !i in
        i := !i + 1
      in
      let+ () =
        Scope.run @@ fun scope ->
        let _ =
          defer scope @@ fun () ->
          let () = check ~here:[%here] 0 in
          let* () = Future.yield () in
          let+ () = Future.yield () in
          check ~here:[%here] 2
        and _ =
          defer scope @@ fun () ->
          let () = check ~here:[%here] 1 in
          let* () = Future.yield () in
          let+ () = Future.yield () in
          check ~here:[%here] 3
        in
        return ()
      in
      check ~here:[%here] 4
  end

  let check name impl =
    let open Alcotest in
    run name
      [
        ( "Blocking",
          Blocking.
            [
              test_case "sequence" `Quick @@ impl sequence;
              test_case "concurrent" `Quick @@ impl concurrent;
            ] );
        ( "Background",
          Background.[ test_case "concurrent" `Quick @@ impl concurrent ] );
        ("Scope", Scope.[ test_case "join" `Quick @@ impl join ]);
      ]
end
