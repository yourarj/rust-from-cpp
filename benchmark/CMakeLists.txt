# CMakeList.txt : CMake project for StringBenchmarks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.11)

include_directories(${CMAKE_BINARY_DIR}/ruster)
include_directories(../inc)
# Include Google Benchmark
# include(../cmake/GoogleBenchmark.cmake)

# Add source to this project's executable.
add_executable (MyBenchamrk "MyBenchmark.cpp" "MyBenchmark.h")

# Link Google Benchmark to the project
target_link_libraries(MyBenchamrk benchmark::benchmark)

# Link Shlwapi to the project
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(MyBenchamrk Shlwapi)
endif()

# TODO: Add tests and install targets if needed.