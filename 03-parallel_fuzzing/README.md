# Lesson 03 - parallel fuzzing

Build variant
```shell
afl-clang-lto -w program.c -o program
AFL_USE_ASAN=1 afl-clang-lto -w program.c -o program_asan
AFL_USE_UBSAN=1 afl-clang-lto -w program.c -o program_ubsan
AFL_LLVM_CMPLOG=1 afl-clang-lto -w program.c -o program_cmplog
AFL_LLVM_LAF_ALL=1 afl-clang-lto -w program.c -o program_laf
```

Parallel fuzzing
```shell
afl-fuzz -M main -i input -o sync_output -- ./program
afl-fuzz -S fuzzer01 -i input -o sync_output -- ./program_asan
afl-fuzz -S fuzzer02 -i input -o sync_output -- ./program_ubsan
afl-fuzz -S fuzzer03 -i input -o sync_output -c 0 -- ./program_cmplog
afl-fuzz -S fuzzer04 -i input -o sync_output -c 0 -l 2AT -- ./program_cmplog
afl-fuzz -S fuzzer05 -i input -o sync_output -- ./program_laf
afl-fuzz -S fuzzer06 -i input -o sync_output -- ./program_laf
```

Using tmux:
```shell
./tmux.sh
```