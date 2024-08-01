cmake_minimum_required(VERSION 3.0)
project(novaledger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
endif()

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Add include directories
include_directories(${OPENSSL_INCLUDE_DIR})

# Add the executable
add_executable(novaledger src/main.cpp src/wallet.cpp src/crypto.cpp)

# Link OpenSSL libraries
target_link_libraries(novaledger ${OPENSSL_LIBRARIES})