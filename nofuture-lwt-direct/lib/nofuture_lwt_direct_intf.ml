module type S = sig
  include
    Nofuture.S_IO
      with type 'a Background.t = 'a Lwt.t
       and type 'a Blocking.t = 'a
       and type Scope.t = Lwt_switch.t

  module In_channel : sig
    include module type of In_channel

    val of_stream : ?close:(unit -> unit Blocking.t) -> string Lwt_stream.t -> t
    val to_stream : t -> string Lwt_stream.t
  end
end
