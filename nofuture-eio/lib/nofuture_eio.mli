include
  Nofuture.S
    with type 'a Blocking.t = 'a
     and type Scope.t = Eio.Switch.t
     and type 'a Background.t = 'a Eio.Promise.or_exn
     and type In_channel.t = [ Eio.Flow.source_ty | `Close ] Eio.Resource.t
     and type Out_channel.t = [ Eio.Flow.sink_ty | `Close ] Eio.Resource.t
