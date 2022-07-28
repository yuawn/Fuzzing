# Lesson 04 - persistent mode

Fuzzing harness:
```c
#include <stdio.h>
#include <stdint.h>

#include <demo.h>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {

    if (size >= 4) {

        demo_vuln_api((char*)data);

    }

    return 0;

}
```

Build fuzzing harness with libAFLDriver.a
```shell
afl-clang-lto -I. -L. harness.cc ../env/AFLplusplus/libAFLDriver.a -ldemo -o harness
```

Fuzzing with persistent mode
```shell
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
afl-fuzz -i input -o output -- ./harness
```

## Reference
- [https://github.com/AFLplusplus/AFLplusplus/tree/stable/utils/aflpp_driver](https://github.com/AFLplusplus/AFLplusplus/tree/stable/utils/aflpp_driver)