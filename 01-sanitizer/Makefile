all:
	afl-clang-lto -w program.c -o program
	mkdir -p input
	echo -ne "\x00" > input/seed0

clean:
	rm -rf input output program program_asan_instrumented