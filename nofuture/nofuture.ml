(** [nofuture] is a unified monadic API for OCaml concurrency libraries. *)

module type S = sig
  (** Core primitive of concurrent code.

      A [Blocking.t] is a computation that can block in some fashion, such as
      waiting on i/o, sleeping, acquiring a mutex, etc. The main purpose of a
      concurrency library is to ensure other computations can still carry on
      while on is blocked. This is achieved through this monadic API.

      Note that this is not the primitive to ensure concurrency of computations.
      Consider the following example:

      {[
        let+ result_a = compute_a ()
        and+ result_b = compute_b () in
        combine result_a result_b
      ]}

      This expresses that there are no dependencies between [compute_a] and
      [compute_b] and thus they CAN be run concurrently, while chaining two
      [let+] would force sequentiallity. Depending on the backend it doesn't
      mean that they WILL run concurrently. If concurrence is required either
      for performances or correctness -- eg. the two computations wait on each
      other -- then refer to the {!Deffered} module.

      Because of this:
      - If sequentiality is required, enforce it by chaining [bind]s.
      - If concurrency is required, see {!Background.}
      - If concurrency is not important but can't hurt, use combiners such as
        [both] and [all] to express the fact there are no intrinsic dependencies
        between computations.

      Exceptions escaping a blocking computation must be handled with
      {!Blocking.catch}.

      In other cruder words, this is not a concurrency tool, this is a plumbing
      primitive you must constraint your code with to give a chance to the
      concurrency backend to interleave blocking computation. It is required by
      monadic concurrency backend ({!Lwt}, {!Async}) and a noop in effect based
      concurrency backends ({!Eio}). Monadic backend will probably run
      [result_a] and [result_b] concurrently while effect backend won't.

      In even cruder words, this is ['a Lwt.t] in {!Lwt}, ['a Deferred.t] in
      {!Async} and ['a] in {!Eio}. *)
  module Blocking : sig
    (** A blocking computation.

        A ['a t] will yield a value of type ['a], possibly blocking along the
        way, but not preventing other blocking computation from running while
        doing so. *)
    type +'a t

    (** [bind v ~f] is the monadic bind. *)
    val bind : 'a t -> f:('a -> 'b t) -> 'b t

    (** [return v] is the monadic return.

        It is a possibly blocking computation that will always immediately yield
        [v]. *)
    val return : 'a -> 'a t

    (** [map v ~f] is the monadic map.

        It is conceptually equivalent to [bind v ~f:(fun v -> return (f v))],
        but possibly more efficient and should be preferred where applicable. *)
    val map : 'a t -> f:('a -> 'b) -> 'b t

    (** [both a b] is the computation that yields both results of [a] and [b].

        [a] and [b] MAY be run concurrently.*)
    val both : 'a t -> 'b t -> ('a * 'b) t

    (** [all comutations] is the computation that yields the results of all
        [computations].

        The [comuptations] MAY be run concurrently.*)
    val all : 'a t list -> 'a list t

    (** [catch f handle] runs [f] and handles escaping exception with [handle]. *)
    val catch : (unit -> 'a t) -> (exn -> 'a t) -> 'a t
  end

  include module type of Blocking

  (** Core primitive to run computations concurrently.

      A [Background.t] is a computation that will run in the background, not
      blocking the *current* execution thread until it is awaited.

      In echo to the {!Blocking} example that does not ensures concurrency, this
      code does:
      {[
        Scope.run @@ fun scope ->
        let a = defer scope compute_a
        and b = defer scope compute_b in
        let+ result_a = await a
        and+ result_b = await b in
        combine result_a result_b
      ]}*)
  module Background : sig
    (** A background computation. *)
    type 'a t

    (** [make ()] returns [(background, resolve)] where [background] is a new
        background computation that will complete with value [v] when
        [resolve v] is called. *)
    val make : unit -> 'a t * ('a -> unit)
  end

  module Scope : sig
    type t

    val run : ?name:string -> (t -> 'res Blocking.t) -> 'res Blocking.t
  end

  (** [defer scope f] creates a background computation that runs [f] without
      blocking the current thread. *)
  val defer : Scope.t -> (unit -> 'a t) -> 'a Background.t

  (** [await background] transforms [background] in a blocking computation,
      possibly blocking immediately until it is done depending on the backend. *)
  val await : 'a Background.t -> 'a Blocking.t

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
