include
  Nofuture.S
    with type 'a Blocking.t = 'a Async.Deferred.t
     and type Scope.t = Async.Monitor.t
     and type 'a Background.t = 'a Async.Deferred.t
     and type Out_channel.t = Async.Writer.t

module In_channel : sig
  include module type of In_channel

  val of_reader : Async.Reader.t -> t
end
