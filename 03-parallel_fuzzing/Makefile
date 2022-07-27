all:
	afl-clang-lto -w program.c -o program
	AFL_USE_ASAN=1 afl-clang-lto -w program.c -o program_asan
	AFL_USE_UBSAN=1 afl-clang-lto -w program.c -o program_ubsan
	AFL_LLVM_CMPLOG=1 afl-clang-lto -w program.c -o program_cmplog
	AFL_LLVM_LAF_ALL=1 afl-clang-lto -w program.c -o program_laf
	mkdir -p input
	echo -ne "\x00" > input/seed0

clean:
	rm -rf input sync_output program program_asan program_ubsan program_cmplog program_laf