# Lesson 01 - Use sanitizer to detect bugs

Without ASAN, the fuzzer cannot detect the bug even if it reached the bug.
```shell
afl-fuzz -i input -o output -- ./program
```

Build target program with AddressSanitizer instrumentation
```shell
AFL_USE_ASAN=1 afl-clang-lto -w program.c -o program_asan_instrumented
```

Catch the bug!
```
afl-fuzz -i input -o output -- ./program_asan_instrumented
```

## More
```
gcc-10 -fsanitize=address -g program.c -o program
clang-14 -g -fsanitize=address -w program.c -o program
```