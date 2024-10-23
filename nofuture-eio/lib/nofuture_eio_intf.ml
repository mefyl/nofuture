module Flow = struct
  type 'source Eio.Flow.read_method += String of ('source -> string option)
end

module type S =
  Nofuture.S_IO
    with type 'a Blocking.t = 'a
     and type Scope.t = Eio.Switch.t
     and type 'a Background.t = 'a Eio.Promise.or_exn
     and type In_channel.t = [ Eio.Flow.source_ty | `Close ] Eio.Resource.t
     and type Out_channel.t = [ Eio.Flow.sink_ty | `Close ] Eio.Resource.t
     and type In_channel.t = [ Eio.Flow.source_ty | `Close ] Eio.Resource.t
     and type Out_channel.t = [ Eio.Flow.sink_ty | `Close ] Eio.Resource.t
