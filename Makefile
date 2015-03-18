all: eval

release: evalrelease

evalrelease: eval.c
	clang eval.c array.c -oeval -lm -lz -Wall -O2

eval: eval.c
	clang eval.c array.c -oeval  -lm -lz -Wall -O0 -g -fsanitize=undefined -fsanitize=address

run: eval
	./eval

.PHONY: all run
