all:
	afl-clang-lto -w program.c -o program
	afl-clang-lto -DSPLIT -w program.c -o program_split
	mkdir -p input
	echo -ne "\x00" > input/seed0

clean:
	rm -rf input output program program_split dictionary.dict