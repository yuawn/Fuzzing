all:
	clang-14 `llvm-config-14 --cxxflags` -shared -fPIC demo-pass.so.cc -o demo-pass.so
	clang-14 `llvm-config-14 --cflags` -fPIC -c demo-rt.o.c -o demo-rt.o
	clang-14 `llvm-config-14 --cflags` -fexperimental-new-pass-manager -fpass-plugin=./demo-pass.so ./demo-rt.o program.c -o program

clean:
	rm -f demo-pass.so demo-rt.o program