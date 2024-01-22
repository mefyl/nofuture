all:
	dune build @default @doc

check:
	dune build @runtest
