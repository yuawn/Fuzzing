# Lesson 07 - Symbolic execution maze with KLEE

**In this lesson, we use LLVM 11**

Run KLEE
```
clang-11 -DKLEE -emit-llvm -c maze.c
klee --emit-all-errors maze.bc 1>/dev/null
```

View .ktest file
```
ktest-tool klee-last/testXXXXXX.ktest
```

Reference
- [https://feliam.wordpress.com/2010/10/07/the-symbolic-maze](https://feliam.wordpress.com/2010/10/07/the-symbolic-maze)