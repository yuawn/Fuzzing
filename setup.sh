#!/bin/bash -ex

mkdir -p env; cd env
SRC=$(pwd)

# common setup
sudo apt update
sudo apt install -y libz3-dev
# sudo apt install -y python3-tabulate
# sudo apt install -y clang-11 llvm-11 llvm-11-dev llvm-11-tools
# LLVM
sudo apt install -y lsb-release wget software-properties-common
if [ ! -f "llvm.sh" ]; then
    wget https://apt.llvm.org/llvm.sh
    chmod +x llvm.sh
fi
sudo ./llvm.sh 11
sudo ./llvm.sh 14


# Build STP solver
# sudo apt install -y cmake bison flex libboost-all-dev python perl zlib1g-dev minisat
# git clone -b 2.3.3 --depth 1 https://github.com/stp/stp.git
# cd stp; mkdir build; cd build
# cmake ..
# make -j $(nproc)
# sudo make install
# cd $SRC 

# Build Z3 solver
# pip3 install z3-solver
# git clone -b z3-4.10.1 --depth 1 https://github.com/Z3Prover/z3.git
# cd z3
# CXX=clang++-11 CC=clang-11 python3 scripts/mk_make.py
# cd build
# make -j $(nproc)
# sudo make install
# cd $SRC

# Build KLEE
sudo apt install -y build-essential cmake curl file g++-multilib gcc-multilib git libcap-dev libunwind-dev libgoogle-perftools-dev libncurses5-dev libsqlite3-dev libtcmalloc-minimal4 python3-pip unzip graphviz doxygen
sudo pip3 install lit wllvm

# klee-uclibc
if [ ! -d "klee-uclibc" ]; then
    git clone -b klee_uclibc_v1.3 --depth 1 https://github.com/klee/klee-uclibc.git
fi
cd klee-uclibc
./configure --make-llvm-lib --with-cc clang-11 --with-llvm-config llvm-config-11
make -j $(nproc)
cd $SRC

# KLEE
if [ ! -d "klee" ]; then
    git clone -b v2.3 --depth 1 https://github.com/klee/klee.git
fi
cd klee; mkdir -p build; cd build
cmake \
    -DENABLE_SOLVER_Z3=ON \
    -DENABLE_POSIX_RUNTIME=ON \
    -DENABLE_KLEE_UCLIBC=ON \
    -DKLEE_UCLIBC_PATH=../../klee-uclibc \
    -DLLVM_CONFIG_BINARY=/usr/bin/llvm-config-11 \
    ..
    # -DENABLE_SOLVER_STP=ON \
make -j $(nproc)
# make systemtests
sudo make install
cd $SRC


# Build AFL++
sudo apt install -y build-essential python3-dev automake cmake git flex bison libglib2.0-dev libpixman-1-dev python3-setuptools cargo libgtk-3-dev
sudo apt install -y gcc-$(gcc --version|head -n1|sed 's/\..*//'|sed 's/.* //')-plugin-dev libstdc++-$(gcc --version|head -n1|sed 's/\..*//'|sed 's/.* //')-dev
if [ ! -d "AFLplusplus" ]; then
    git clone -b 4.01c --depth 1 https://github.com/AFLplusplus/AFLplusplus.git
fi
cd AFLplusplus
make LLVM_CONFIG=llvm-config-14
sudo make install