module type S = sig
  include
    Nofuture.S
      with type 'a Blocking.t = 'a Lwt.t
       and type Scope.t = Lwt_switch.t
       and type 'a Background.t = 'a Lwt.t

  module In_channel : sig
    include module type of In_channel

    val of_stream : ?close:(unit -> unit Blocking.t) -> string Lwt_stream.t -> t
    val to_stream : t -> string Lwt_stream.t
  end
end
