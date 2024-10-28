(alias (name extdeps) (deps opam/nofuture.opam.extdeps))
(subdir opam
 (rule (target nofuture.%{version:nofuture}.opam)
  (deps (:opam ../nofuture.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture.opam.locked)
  (action (run %{bin:opam} lock nofuture)))
 (rule (mode (promote (until-clean))) (target nofuture.opam.extdeps)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt))))
 (rule (target nofuture-ios.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
     %{dep:../nofuture.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-ios.%{version:nofuture}.opam)
  (deps (:opam nofuture-ios.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-ios.opam.locked)
  (action (run %{bin:opam} lock nofuture-ios)))
 (rule (mode (promote (until-clean))) (target nofuture.opam.extdeps-ios)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-ios.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain ios))))
 (rule (target nofuture-macos.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-macos --input
     %{dep:../nofuture.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-macos.%{version:nofuture}.opam)
  (deps (:opam nofuture-macos.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-macos.opam.locked)
  (action (run %{bin:opam} lock nofuture-macos)))
 (rule (mode (promote (until-clean))) (target nofuture.opam.extdeps-macos)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-macos.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain macos))))
 (rule (target nofuture-windows.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-windows --input
     %{dep:../nofuture.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-windows.%{version:nofuture}.opam)
  (deps (:opam nofuture-windows.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-windows.opam.locked)
  (action (run %{bin:opam} lock nofuture-windows)))
 (rule (mode (promote (until-clean))) (target nofuture.opam.extdeps-windows)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-windows.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain windows))))
 (rule (target nofuture-android.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-android --input
     %{dep:../nofuture.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-android.%{version:nofuture}.opam)
  (deps (:opam nofuture-android.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-android.opam.locked)
  (action (run %{bin:opam} lock nofuture-android)))
 (rule (mode (promote (until-clean))) (target nofuture.opam.extdeps-android)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-android.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain android)))))
(alias (name extdeps) (deps opam/nofuture-async.opam.extdeps))
(subdir opam
 (rule (target nofuture-async.%{version:nofuture-async}.opam)
  (deps (:opam ../nofuture-async.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-async.opam.locked)
  (action (run %{bin:opam} lock nofuture-async)))
 (rule (mode (promote (until-clean))) (target nofuture-async.opam.extdeps)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-async.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt))))
 (rule (target nofuture-async-ios.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
     %{dep:../nofuture-async.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-async-ios.%{version:nofuture-async}.opam)
  (deps (:opam nofuture-async-ios.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-async-ios.opam.locked)
  (action (run %{bin:opam} lock nofuture-async-ios)))
 (rule (mode (promote (until-clean)))
  (target nofuture-async.opam.extdeps-ios)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-async-ios.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain ios))))
 (rule (target nofuture-async-macos.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-macos --input
     %{dep:../nofuture-async.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-async-macos.%{version:nofuture-async}.opam)
  (deps (:opam nofuture-async-macos.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-async-macos.opam.locked)
  (action (run %{bin:opam} lock nofuture-async-macos)))
 (rule (mode (promote (until-clean)))
  (target nofuture-async.opam.extdeps-macos)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-async-macos.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain macos))))
 (rule (target nofuture-async-windows.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-windows --input
     %{dep:../nofuture-async.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-async-windows.%{version:nofuture-async}.opam)
  (deps (:opam nofuture-async-windows.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-async-windows.opam.locked)
  (action (run %{bin:opam} lock nofuture-async-windows)))
 (rule (mode (promote (until-clean)))
  (target nofuture-async.opam.extdeps-windows)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-async-windows.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain windows))))
 (rule (target nofuture-async-android.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-android --input
     %{dep:../nofuture-async.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-async-android.%{version:nofuture-async}.opam)
  (deps (:opam nofuture-async-android.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-async-android.opam.locked)
  (action (run %{bin:opam} lock nofuture-async-android)))
 (rule (mode (promote (until-clean)))
  (target nofuture-async.opam.extdeps-android)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-async-android.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain android)))))
(alias (name extdeps) (deps opam/nofuture-eio.opam.extdeps))
(subdir opam
 (rule (target nofuture-eio.%{version:nofuture-eio}.opam)
  (deps (:opam ../nofuture-eio.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-eio.opam.locked)
  (action (run %{bin:opam} lock nofuture-eio)))
 (rule (mode (promote (until-clean))) (target nofuture-eio.opam.extdeps)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-eio.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt))))
 (rule (target nofuture-eio-ios.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
     %{dep:../nofuture-eio.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-eio-ios.%{version:nofuture-eio}.opam)
  (deps (:opam nofuture-eio-ios.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-eio-ios.opam.locked)
  (action (run %{bin:opam} lock nofuture-eio-ios)))
 (rule (mode (promote (until-clean))) (target nofuture-eio.opam.extdeps-ios)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-eio-ios.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain ios))))
 (rule (target nofuture-eio-macos.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-macos --input
     %{dep:../nofuture-eio.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-eio-macos.%{version:nofuture-eio}.opam)
  (deps (:opam nofuture-eio-macos.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-eio-macos.opam.locked)
  (action (run %{bin:opam} lock nofuture-eio-macos)))
 (rule (mode (promote (until-clean)))
  (target nofuture-eio.opam.extdeps-macos)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-eio-macos.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain macos))))
 (rule (target nofuture-eio-windows.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-windows --input
     %{dep:../nofuture-eio.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-eio-windows.%{version:nofuture-eio}.opam)
  (deps (:opam nofuture-eio-windows.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-eio-windows.opam.locked)
  (action (run %{bin:opam} lock nofuture-eio-windows)))
 (rule (mode (promote (until-clean)))
  (target nofuture-eio.opam.extdeps-windows)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-eio-windows.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain windows))))
 (rule (target nofuture-eio-android.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-android --input
     %{dep:../nofuture-eio.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-eio-android.%{version:nofuture-eio}.opam)
  (deps (:opam nofuture-eio-android.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-eio-android.opam.locked)
  (action (run %{bin:opam} lock nofuture-eio-android)))
 (rule (mode (promote (until-clean)))
  (target nofuture-eio.opam.extdeps-android)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-eio-android.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain android)))))
(alias (name extdeps) (deps opam/nofuture-lwt.opam.extdeps))
(subdir opam
 (rule (target nofuture-lwt.%{version:nofuture-lwt}.opam)
  (deps (:opam ../nofuture-lwt.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt)))
 (rule (mode (promote (until-clean))) (target nofuture-lwt.opam.extdeps)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt))))
 (rule (target nofuture-lwt-ios.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
     %{dep:../nofuture-lwt.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-ios.%{version:nofuture-lwt}.opam)
  (deps (:opam nofuture-lwt-ios.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-ios.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-ios)))
 (rule (mode (promote (until-clean))) (target nofuture-lwt.opam.extdeps-ios)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-ios.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain ios))))
 (rule (target nofuture-lwt-macos.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-macos --input
     %{dep:../nofuture-lwt.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-macos.%{version:nofuture-lwt}.opam)
  (deps (:opam nofuture-lwt-macos.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-macos.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-macos)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt.opam.extdeps-macos)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-macos.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain macos))))
 (rule (target nofuture-lwt-windows.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-windows --input
     %{dep:../nofuture-lwt.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-windows.%{version:nofuture-lwt}.opam)
  (deps (:opam nofuture-lwt-windows.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-windows.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-windows)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt.opam.extdeps-windows)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-windows.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain windows))))
 (rule (target nofuture-lwt-android.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-android --input
     %{dep:../nofuture-lwt.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-android.%{version:nofuture-lwt}.opam)
  (deps (:opam nofuture-lwt-android.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-android.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-android)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt.opam.extdeps-android)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-android.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain android)))))
(alias (name extdeps) (deps opam/nofuture-lwt-jsoo.opam.extdeps))
(subdir opam
 (rule (target nofuture-lwt-jsoo.%{version:nofuture-lwt-jsoo}.opam)
  (deps (:opam ../nofuture-lwt-jsoo.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-jsoo.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-jsoo)))
 (rule (mode (promote (until-clean))) (target nofuture-lwt-jsoo.opam.extdeps)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-jsoo.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt))))
 (rule (target nofuture-lwt-jsoo-ios.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
     %{dep:../nofuture-lwt-jsoo.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-jsoo-ios.%{version:nofuture-lwt-jsoo}.opam)
  (deps (:opam nofuture-lwt-jsoo-ios.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-jsoo-ios.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-jsoo-ios)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt-jsoo.opam.extdeps-ios)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-jsoo-ios.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain ios))))
 (rule (target nofuture-lwt-jsoo-macos.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-macos --input
     %{dep:../nofuture-lwt-jsoo.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-jsoo-macos.%{version:nofuture-lwt-jsoo}.opam)
  (deps (:opam nofuture-lwt-jsoo-macos.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-jsoo-macos.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-jsoo-macos)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt-jsoo.opam.extdeps-macos)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-jsoo-macos.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain macos))))
 (rule (target nofuture-lwt-jsoo-windows.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-windows --input
     %{dep:../nofuture-lwt-jsoo.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-jsoo-windows.%{version:nofuture-lwt-jsoo}.opam)
  (deps (:opam nofuture-lwt-jsoo-windows.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-jsoo-windows.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-jsoo-windows)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt-jsoo.opam.extdeps-windows)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-jsoo-windows.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain windows))))
 (rule (target nofuture-lwt-jsoo-android.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-android --input
     %{dep:../nofuture-lwt-jsoo.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-jsoo-android.%{version:nofuture-lwt-jsoo}.opam)
  (deps (:opam nofuture-lwt-jsoo-android.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-jsoo-android.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-jsoo-android)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt-jsoo.opam.extdeps-android)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-jsoo-android.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain android)))))
(alias (name extdeps) (deps opam/nofuture-lwt-unix.opam.extdeps))
(subdir opam
 (rule (target nofuture-lwt-unix.%{version:nofuture-lwt-unix}.opam)
  (deps (:opam ../nofuture-lwt-unix.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-unix.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-unix)))
 (rule (mode (promote (until-clean))) (target nofuture-lwt-unix.opam.extdeps)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-unix.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt))))
 (rule (target nofuture-lwt-unix-ios.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-ios --input
     %{dep:../nofuture-lwt-unix.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-unix-ios.%{version:nofuture-lwt-unix}.opam)
  (deps (:opam nofuture-lwt-unix-ios.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-unix-ios.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-unix-ios)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt-unix.opam.extdeps-ios)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-unix-ios.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain ios))))
 (rule (target nofuture-lwt-unix-macos.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-macos --input
     %{dep:../nofuture-lwt-unix.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-unix-macos.%{version:nofuture-lwt-unix}.opam)
  (deps (:opam nofuture-lwt-unix-macos.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-unix-macos.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-unix-macos)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt-unix.opam.extdeps-macos)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-unix-macos.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain macos))))
 (rule (target nofuture-lwt-unix-windows.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-windows --input
     %{dep:../nofuture-lwt-unix.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-unix-windows.%{version:nofuture-lwt-unix}.opam)
  (deps (:opam nofuture-lwt-unix-windows.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-unix-windows.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-unix-windows)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt-unix.opam.extdeps-windows)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-unix-windows.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain windows))))
 (rule (target nofuture-lwt-unix-android.opam) (mode (promote (until-clean)))
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite-android --input
     %{dep:../nofuture-lwt-unix.opam} --cross
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt,base,base64,cohttp-lwt,ezjsonm,fmt,hlist,logs,lwt,ptime,sexplib,uri
     --cross-both
     bake,fmt,landmarks-ppx,ppx_deriving,ppx_hash,ppx_here,semver2
     --cross-exclude ""))))
 (rule (target nofuture-lwt-unix-android.%{version:nofuture-lwt-unix}.opam)
  (deps (:opam nofuture-lwt-unix-android.opam))
  (action
   (with-stdout-to %{target}
    (progn (cat %{opam})
     (run git log
      "--pretty=url { src: \"git://git@gitlab.routine.co:routine/nofuture#%H\" }"
      -n1)))))
 (rule (deps (universe)) (target nofuture-lwt-unix-android.opam.locked)
  (action (run %{bin:opam} lock nofuture-lwt-unix-android)))
 (rule (mode (promote (until-clean)))
  (target nofuture-lwt-unix.opam.extdeps-android)
  (action
   (with-stdout-to %{target}
    (run %{dep:../.logistic/dune/extdeps/extdeps.exe} rewrite --input
     %{dep:nofuture-lwt-unix-android.opam.locked} --local
     nofuture,nofuture-async,nofuture-eio,nofuture-lwt,nofuture-lwt-jsoo,nofuture-lwt-unix,acid,bake,hlist,sqml,timmy,timmy-lwt
     --toolchain android)))))
