(lang dune 3.12)

(name nofuture)

(generate_opam_files true)

(license LGPL-3.0-or-later)

(maintainers "mefyl <mefyl@gruntech.org>")

(authors "mefyl <mefyl@gruntech.org>")

(version 0.1.0)

(homepage https://gitlab.routine.co/routine/nofuture)

(bug_reports https://gitlab.routine.co/routine/nofuture/-/issues)

(source
 (uri git+https://gitlab.routine.co/routine/nofuture.git))

(executables_implicit_empty_intf true)

(using mdx 0.4)

(package
 (name nofuture)
 (synopsis "Unified concurrency API")
 (depends
  (mdx :with-test)
  (odoc :with-doc)))

(package
 (name nofuture-async)
 (synopsis "Async implementation of nofuture")
 (depends
  async
  (nofuture
   (= :version))
  (alcotest :with-test)
  (ppx_here :with-test)))

(package
 (name nofuture-eio)
 (synopsis "Eio implementation of nofuture")
 (depends
  (eio
   (>= 1.0))
  (nofuture
   (= :version))
  (alcotest :with-test)
  (eio_main :with-test)
  (ppx_here :with-test)))

(package
 (name nofuture-lwt)
 (synopsis "Lwt implementation of nofuture")
 (depends
  lwt
  (nofuture
   (= :version))
  (alcotest :with-test)
  (ppx_here :with-test)))

(package
 (name nofuture-lwt-unix)
 (synopsis "Lwt implementation of nofuture for Unix")
 (depends
  lwt
  (nofuture-lwt
   (= :version))
  (alcotest :with-test)
  (ppx_here :with-test)))

(package
 (name nofuture-lwt-jsoo)
 (synopsis "Lwt implementation of nofuture for js_of_ocaml")
 (depends
  lwt
  (nofuture-lwt
   (= :version))
  js_of_ocaml
  js_of_ocaml-lwt
  (alcotest :with-test)
  (ppx_here :with-test)))
