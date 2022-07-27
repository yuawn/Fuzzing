#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>

#include <sys/mman.h>
#ifndef __HAIKU__
  #include <sys/syscall.h>
#endif
#ifndef USEMMAP
  #include <sys/shm.h>
#endif
#include <sys/wait.h>
#include <sys/types.h>

#if !__GNUC__
  #include "llvm/Config/llvm-config.h"
#endif


void __demo_func() {

  puts("Hi, I'm instrumentation code :D");

}