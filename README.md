# Fuzzing

Fuzzing tutorial with easy to learn labs.

# Lessons
| Lesson | keyword | Lab |
| ------------- | ------------- | ------------- |
| [Lesson 00 - Fuzzing with AFL++](00-fuzzing) | afl-cc, afl-clang-lto, fuzzing | :white_check_mark: |
| [Lesson 01 - Use sanitizer to catch silent bugs](01-sanitizer) | AddressSanitizer(ASAN) | :white_check_mark: |
| [Lesson 02 - Improve code coverage using dictionary](02-dictionary) | dictionary, branch constraint, split-comparison | :white_check_mark: |
| [Lesson 03 - Parallel fuzzing: combine the advantages of each fuzzer](03-parallel_fuzzing) | parallel fuzzing, seed pool syncing | :white_check_mark: |
| [Lesson 04 - Increase fuzzing performance by persistent mode](04-persistent_mode) | fuzzing harness, persistent mode | :white_check_mark: |
| [Lesson 05 - Write a LLVM Pass to do binary instrumentation](05-LLVM_Pass) | LLVM Pass, binary instrumentation | :white_check_mark: |
| [Lesson 06 - Integrate custom LLVM Pass into AFL++](06-AFLpp_LLVM_Pass_integration) | custom LLVM Pass in AFL++, integration example | :white_check_mark: |
| [Lesson 07 - Playing symbolic execution on a maze with KLEE](07-KLEE_symbolic_execution) | symbolic execution, KLEE | :white_check_mark: |


## Setup
```shell
./setup.sh
make
```

## Environment
| Name | Version |
| ---- | ------- |
| LLVM (clang, lld) | [14.0.6](https://github.com/llvm/llvm-project/releases/tag/llvmorg-14.0.6) |
| AFL++ | [4.01c](https://github.com/AFLplusplus/AFLplusplus/releases/tag/4.01c) |
| KLEE | [v2.3](https://github.com/klee/klee/releases/tag/v2.3) |
