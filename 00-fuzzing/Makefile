all:
	afl-clang-lto -w program.c -o program
	afl-clang-lto -w -DFILE_INPUT program.c -o program_file_input

clean:
	rm -rf input output program program_file_input