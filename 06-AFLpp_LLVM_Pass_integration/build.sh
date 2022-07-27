#!/bin/bash -ex

if [ ! -d "AFLplusplus" ]; then
    git clone -b 4.01c --depth 1 https://github.com/AFLplusplus/AFLplusplus.git
    git -C AFLplusplus apply ../integration.diff
fi

cp llvm-pass/* AFLplusplus/instrumentation
cd AFLplusplus
make LLVM_CONFIG=llvm-config-14