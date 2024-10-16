include module type of Nofuture_lwt_intf

include
  S
    with type 'a Blocking.t = 'a Lwt.t
     and type Scope.t = Lwt_switch.t
     and type 'a Background.t = 'a Lwt.t
