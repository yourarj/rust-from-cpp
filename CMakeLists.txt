if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif ()

project(cxx_example)
cmake_minimum_required(VERSION 3.15)

set (CMAKE_CXX_STANDARD 17)

message("-- CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message("-- CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message("-- CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("-- CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")

option(ENABLE_LTO "Enable cross language linking time optimization" ON)
if(ENABLE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT supported OUTPUT error)
  if(supported)
      message(STATUS "IPO / LTO enabled")
      set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
      add_link_options(-fuse-ld=lld)
  else()
      message(STATUS "IPO / LTO not supported: <${error}>")
  endif()
endif()

include_directories(${CMAKE_BINARY_DIR}/ruster)
include_directories(inc)

add_subdirectory(ruster)

add_executable(main main.cpp)

if(CMAKE_COMPILER_IS_GNUCXX)
    message("-- Linking with GNUCXX")
    set(
        CMAKE_STATIC_LINKER_FLAGS_RELEASE
            "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} -flto"
    )
else()
    message("-- Not linking with GNUCXX")
endif()

target_link_libraries(main ruster)
