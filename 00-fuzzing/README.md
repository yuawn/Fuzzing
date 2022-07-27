# Lesson 00 - Fuzzing with AFL++

Build target program with instrumentation to capture run-time information like code-coverage
```shell
afl-clang-lto -w program.c -o program
```

Create corpus directory and initial seed
```shell
mkdir input
echo -ne "\x00" > input/seed0
```

Fuzz the program
```shell
afl-fuzz -i input -o output -- ./program
```

File input
```shell
afl-clang-lto -w -DFILE program.c -o program_file_input
afl-fuzz -i input -o output -- ./program_file_input @@
```