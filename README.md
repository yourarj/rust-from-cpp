# rust-from-cpp

This project aims to experiment integrating rust in C++ project

## Setup (Optional)

Considering Ubuntu

`sudo apt install clang lldb llvm lld`

## Pre-requisites

If you are running with `-DENABLE_LTO=ON` switch, make sure that two environment variables `CC=clang-14` and `CXX=clang++-14` are set according to available clang version.

Rust llvm and local llvm should have same version.

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
```
