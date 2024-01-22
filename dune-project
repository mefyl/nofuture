(lang dune 3.12)

(name nofuture)

(generate_opam_files true)

(license LGPL-3.0-or-later)

(maintainers "mefyl <mefyl@gruntech.org>")

(authors "mefyl <mefyl@gruntech.org>")

(version 0.0.1)

(homepage https://gitlab.routine.co/routine/nofuture)

(bug_reports https://gitlab.routine.co/routine/nofuture/-/issues)

(source
 (uri git+https://gitlab.routine.co/routine/nofuture.git))

(using mdx 0.4)

(package
 (name nofuture)
 (synopsis "Unified concurrency API")
 (depends
  (mdx :with-test)
  (odoc :with-doc)))

(package
 (name nofuture-lwt)
 (synopsis "Lwt implementation of nofuture")
 (depends nofuture lwt))

(package
 (name nofuture-eio)
 (synopsis "Eio implementation of nofuture")
 (depends nofuture eio))
