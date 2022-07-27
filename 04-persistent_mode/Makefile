all:
	afl-clang-lto -c -Wall -Werror -fpic demo.c
	afl-clang-lto -shared -o libdemo.so demo.o
	afl-clang-lto -I. -L. harness.cc ../env/AFLplusplus/libAFLDriver.a -o harness -ldemo

	mkdir -p input
	echo -ne "\x00" > input/seed0

clean:
	rm -rf input output demo.o libdemo.so harness