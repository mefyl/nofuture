(rule (target nofuture.%{version:nofuture}.opam) (deps (:opam nofuture.opam))
 (action
  (with-stdout-to %{target}
   (progn (cat %{opam})
    (echo
     "url { src: \"git://git@gitlab.routine.co:routine/nofuture#%{version:nofuture}\" }")))))
(rule (target nofuture-ios.opam)
 (action
  (with-stdout-to %{target}
   (run %{dep:.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
    %{dep:nofuture.opam} --cross
    nofuture,nofuture-eio,nofuture-lwt,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
    --cross-both
    bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
    --cross-exclude ""))))
(rule (target nofuture-ios.%{version:nofuture}.opam)
 (deps (:opam nofuture-ios.opam))
 (action
  (with-stdout-to %{target}
   (progn (cat %{opam})
    (echo
     "url { src: \"git://git@gitlab.routine.co:routine/nofuture#%{version:nofuture}\" }")))))
(rule (deps (universe)) (target nofuture.opam.locked)
 (action (run %{bin:opam} lock nofuture)))
(rule (alias extdeps) (mode (promote (until-clean)))
 (target nofuture.opam.extdeps)
 (action
  (with-stdout-to %{target}
   (run %{dep:.logistic/dune/extdeps/extdeps.exe} rewrite --input
    %{dep:nofuture.opam.locked} --local
    nofuture,nofuture-eio,nofuture-lwt,acid,bake,hlist,sqml,timmy,timmy-lwt))))
(rule (target nofuture-eio.%{version:nofuture-eio}.opam)
 (deps (:opam nofuture-eio.opam))
 (action
  (with-stdout-to %{target}
   (progn (cat %{opam})
    (echo
     "url { src: \"git://git@gitlab.routine.co:routine/nofuture#%{version:nofuture-eio}\" }")))))
(rule (target nofuture-eio-ios.opam)
 (action
  (with-stdout-to %{target}
   (run %{dep:.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
    %{dep:nofuture-eio.opam} --cross
    nofuture,nofuture-eio,nofuture-lwt,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
    --cross-both
    bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
    --cross-exclude ""))))
(rule (target nofuture-eio-ios.%{version:nofuture-eio}.opam)
 (deps (:opam nofuture-eio-ios.opam))
 (action
  (with-stdout-to %{target}
   (progn (cat %{opam})
    (echo
     "url { src: \"git://git@gitlab.routine.co:routine/nofuture#%{version:nofuture-eio}\" }")))))
(rule (deps (universe)) (target nofuture-eio.opam.locked)
 (action (run %{bin:opam} lock nofuture-eio)))
(rule (alias extdeps) (mode (promote (until-clean)))
 (target nofuture-eio.opam.extdeps)
 (action
  (with-stdout-to %{target}
   (run %{dep:.logistic/dune/extdeps/extdeps.exe} rewrite --input
    %{dep:nofuture-eio.opam.locked} --local
    nofuture,nofuture-eio,nofuture-lwt,acid,bake,hlist,sqml,timmy,timmy-lwt))))
(rule (target nofuture-lwt.%{version:nofuture-lwt}.opam)
 (deps (:opam nofuture-lwt.opam))
 (action
  (with-stdout-to %{target}
   (progn (cat %{opam})
    (echo
     "url { src: \"git://git@gitlab.routine.co:routine/nofuture#%{version:nofuture-lwt}\" }")))))
(rule (target nofuture-lwt-ios.opam)
 (action
  (with-stdout-to %{target}
   (run %{dep:.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
    %{dep:nofuture-lwt.opam} --cross
    nofuture,nofuture-eio,nofuture-lwt,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
    --cross-both
    bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
    --cross-exclude ""))))
(rule (target nofuture-lwt-ios.%{version:nofuture-lwt}.opam)
 (deps (:opam nofuture-lwt-ios.opam))
 (action
  (with-stdout-to %{target}
   (progn (cat %{opam})
    (echo
     "url { src: \"git://git@gitlab.routine.co:routine/nofuture#%{version:nofuture-lwt}\" }")))))
(rule (deps (universe)) (target nofuture-lwt.opam.locked)
 (action (run %{bin:opam} lock nofuture-lwt)))
(rule (alias extdeps) (mode (promote (until-clean)))
 (target nofuture-lwt.opam.extdeps)
 (action
  (with-stdout-to %{target}
   (run %{dep:.logistic/dune/extdeps/extdeps.exe} rewrite --input
    %{dep:nofuture-lwt.opam.locked} --local
    nofuture,nofuture-eio,nofuture-lwt,acid,bake,hlist,sqml,timmy,timmy-lwt))))
