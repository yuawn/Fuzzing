# Lesson 05 - LLVM Pass

Build the LLVM Pass
```shell
clang-14 `llvm-config-14 --cxxflags` -shared -fPIC afl-demo-pass.so.cc -o afl-demo-pass.so
```

Build object
```
clang-14 `llvm-config-14 --cflags` -fPIC -c afl-demo-rt.o.c -o afl-demo-rt.o
```

Compile program with the Pass
```shell
clang-14 `llvm-config-14 --cflags` -fexperimental-new-pass-manager -fpass-plugin=./afl-demo-pass.so ./afl-demo-rt.o program.c -o program
```