(lang dune 3.0)

(name future)

(generate_opam_files true)

(license LGPL-3.0-or-later)

(maintainers "mefyl <mefyl@gruntech.org>")

(authors "mefyl <mefyl@gruntech.org>")

(version 0.0.1)

(homepage https://gitlab.routine.co/routine/future)

(bug_reports https://gitlab.routine.co/routine/future/-/issues)

(source
 (uri git+https://gitlab.routine.co/routine/future.git))

(package
 (name nofuture)
 (synopsis "Agnostic parallel IO interface"))

(package
 (name nofuture-lwt)
 (synopsis "LWT implementation of nofuture")
 (depends nofuture lwt))

(package
 (name nofuture-eio)
 (synopsis "EIO implementation of nofuture")
 (depends nofuture eio))
