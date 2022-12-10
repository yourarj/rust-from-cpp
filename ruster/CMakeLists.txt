if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_CMD cargo build --verbose)
    set(TARGET_DIR "debug")
else ()
    set(CARGO_CMD cargo build --release --verbose)
    set(TARGET_DIR "release")
endif ()

if(ENABLE_LTO)
    set(RUST_FLAGS "-Clinker-plugin-lto" "-Clinker=clang-13" "-Clink-arg=-fuse-ld=lld-13")
endif()

set(RUSTER_LIB "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_DIR}/libruster.a")

set(RUSTER_CXX "${CMAKE_CURRENT_BINARY_DIR}/ruster.cpp")
add_library(ruster STATIC ${RUSTER_CXX})
add_custom_command(
    OUTPUT ${RUSTER_CXX}
    COMMAND CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} RUSTFLAGS="${RUST_FLAGS}" ${CARGO_CMD}
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/cxxbridge/ruster/src/lib.rs.cc ${RUSTER_CXX}
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/cxxbridge/ruster/src/lib.rs.h ${CMAKE_CURRENT_BINARY_DIR}/ruster.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ruster pthread dl ${RUSTER_LIB})

add_test(NAME ruster_test 
    COMMAND cargo test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

