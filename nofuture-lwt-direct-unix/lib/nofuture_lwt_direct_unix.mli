include
  Nofuture_lwt_direct.S
    with type In_channel.t = Lwt_io.input_channel
     and type Out_channel.t = Lwt_io.output_channel

include Nofuture.TIME with module Blocking := Blocking
