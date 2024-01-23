module Flow = struct
  type 'source Eio.Flow.read_method +=
    | String of ('source -> string option)
    | Bytes of ('source -> Bytes.t option)
end
