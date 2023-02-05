# rust-from-cpp

This project aims to experiment integrating rust in C++ project

## Setup (Optional)

Considering Ubuntu

`sudo apt install clang lldb llvm lld`

## Pre-requisites

If you are running with `-DENABLE_LTO=ON` switch, make sure that two environment variables `CC=clang-14` and `CXX=clang++-14` are set according to available clang version.

Rust llvm and local llvm should have same version.

## Target aarch64
```bash
# add target
rustup target add aarch64-unknown-linux-gnu

# install g++ for aarch64-unknown-linux-gnu
sudo apt-get install g++-aarch64-linux-gnu

# print target spec
rustc +nightly -Z unstable-options --print target-spec-json --target aarch64-unknown-linux-gnu
```

## How to Build & Run

```bash
# install cmake
sudo apt install cmake

# assuming running these commands from project root

# create build dir
mkdir -p build

# cd to build dir
cd build

# build with cross-language LTO off
cmake -DENABLE_LTO=OFF -DCMAKE_BUILD_TYPE=Release ..

# make 
make -j

# run executable
./main

# or a shortcut
# for Release
rm -rf build/ && cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -DENABLE_LTO=OFF && cmake --build build/debug && ./build/debug/main

# for Release
rm -rf build/ && cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release -DENABLE_LTO=OFF && cmake --build build/release && ./build/release/main

# for RelWithDebInfo
rm -rf build/ && cmake -S . -B build/relwithdebinfo -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_LTO=OFF && cmake --build build/relwithdebinfo && ./build/relwithdebinfo/main

```
