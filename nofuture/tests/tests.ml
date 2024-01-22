module Make (Future : Nofuture.S) = struct
  type impl =
    {
      sleep : Mtime.t -> unit Future.t
    }

  let sequence =

end
