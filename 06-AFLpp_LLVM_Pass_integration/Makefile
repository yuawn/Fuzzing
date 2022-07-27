all:
	./build.sh
	./AFLplusplus/afl-clang-lto -w program.c -o program
	AFL_USE_ASAN=1 ./AFLplusplus/afl-clang-lto -w program.c -o program_asan
	AFL_DEMO=1 ./AFLplusplus/afl-clang-lto -w program.c -o program_custom_instrumented
	mkdir -p input
	echo -ne "\x00" > input/seed0

clean:
	rm -rf AFLplusplus input output program program_asan program_custom_instrumented