# rust-from-cpp

This project aims to experiment integrating rust in C++ project

## How to Build & Run

```bash
# create build dir
mkdir -p build

# cd to build dir
cd build

# build with cross-language LTO off
cmake -DENABLE_LTO=OFF -DCMAKE_BUILD_TYPE=Release ..

# run executable
./main
```
