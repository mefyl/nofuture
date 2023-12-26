include
  Nofuture.S
    with type 'a Blocking.t = 'a Lwt.t
     and type Scope.t = Lwt_switch.t
     and type 'a Deferred.t = 'a Lwt.t
     and type In_channel.t = Lwt_io.input_channel
     and type Out_channel.t = Lwt_io.output_channel
