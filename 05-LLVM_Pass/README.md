# Lesson 05 - LLVM Pass

Build the LLVM Pass
```shell
clang-14 `llvm-config-14 --cxxflags` -shared -fPIC demo-pass.so.cc -o demo-pass.so
```

Build object
```
clang-14 `llvm-config-14 --cflags` -fPIC -c demo-rt.o.c -o demo-rt.o
```

Compile program with the Pass
```shell
clang-14 `llvm-config-14 --cflags` -fexperimental-new-pass-manager -fpass-plugin=./demo-pass.so ./demo-rt.o program.c -o program
```