#include <stdio.h>
#include <stdint.h>

#include <demo.h>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {

    if (size >= 4) {

        demo_vuln_api((char*)data);

    }

    return 0;

}