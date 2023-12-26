module type S = sig
  module Blocking : sig
    type +'a t
  end

  type 'a t = 'a Blocking.t

  (* val all : 'a t list -> 'a list t *)
  (* val both : 'a t -> 'b t -> ('a * 'b) t *)
  val bind : 'a t -> f:('a -> 'b t) -> 'b t
  val map : 'a t -> f:('a -> 'b) -> 'b t
  val return : 'a -> 'a t
  val catch : (unit -> 'a Blocking.t) -> (exn -> 'a Blocking.t) -> 'a Blocking.t

  module Scope : sig
    type t

    val run : ?name:string -> (t -> 'res Blocking.t) -> 'res Blocking.t
  end

  module Deferred : sig
    type 'a t

    val make : unit -> 'a t * ('a -> unit)
  end

  val defer : Scope.t -> (unit -> 'a t) -> 'a Deferred.t
  val await : 'a Deferred.t -> 'a t

  module In_channel : sig
    type t

    val close : t -> unit Blocking.t
    val empty : t
    val of_bytes : Bytes.t -> t
    val of_string : string -> t
    val read_char : t -> char option Blocking.t
    val read : t -> Bytes.t Blocking.t
    val read_string : t -> string Blocking.t
    val read_all : t -> Bytes.t Blocking.t
    val read_all_string : t -> string Blocking.t
  end

  module Out_channel : sig
    type t

    val close : t -> unit Blocking.t
    val write : t -> Bytes.t -> unit Blocking.t
    val write_string : t -> string -> unit Blocking.t
  end

  module Mutex : sig
    type t

    val make : unit -> t
    val use : t -> (unit -> 'a Blocking.t) -> 'a Blocking.t
  end

  module Condition : sig
    type t

    val await : ?mutex:Mutex.t -> t -> unit Blocking.t
    val broadcast : t -> unit
    val make : unit -> t
  end
end
