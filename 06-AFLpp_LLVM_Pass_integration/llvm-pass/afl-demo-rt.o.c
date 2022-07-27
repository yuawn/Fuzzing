#ifdef __ANDROID__
  #include "android-ashmem.h"
#endif
#include "config.h"
#include "types.h"
#include "cmplog.h"
#include "llvm-alternative-coverage.h"

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

#ifdef __linux__
  #include "snapshot-inl.h"
#endif

u32    size = 0;
u32    count = 0;
char **addrs = 0;

void __demo_func() {

  puts("Hi, I'm instrumentation code :D");

}

void __demo_record_input(char *addr) {

  if (!count) {

    size = 1;
    count = 1;
    addrs = malloc(size * sizeof(char *));
    addrs[0] = addr;
    return;

  }

  for (u32 i = 0; i < count; ++i)
    if (addr == addrs[i]) return;

  addrs[count++] = addr;

  if (count == size) {

    size *= 2;
    addrs = realloc(addrs, size * sizeof(char *));

  }

}

void __demo_check_fmt(char *fmt) {

  for (int i = 0; i < count; ++i) {

    if (strstr(addrs[i], fmt)) {

      fprintf(stderr, "Format string: \"%s\" found in input data!\n", fmt);
      abort();

    }

  }

}

