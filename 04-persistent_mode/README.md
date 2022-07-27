# Lesson 04 - persistent mode


Build fuzzing harness with libAFLDriver.a
```shell
afl-clang-lto -I. -L. harness.cc ../env/AFLplusplus/libAFLDriver.a -ldemo -o harness
```

Fuzzing with persistent mode
```shell
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
afl-fuzz -i input -o output -- ./harness
```