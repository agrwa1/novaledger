cmake_minimum_required(VERSION 3.29)
project(novaledger)

# MUST USE AT LEAST C++14  
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
# endif()

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Add include directories
# include_directories(${OPENSSL_INCLUDE_DIR} "src/")

# include all files
file(GLOB_RECURSE ALL_FILES "src/*")
message(STATUS "Sources found: ${ALL_FILES}")

# Add the executable
add_executable(novaledger ${ALL_FILES})

target_include_directories(novaledger PUBLIC "src/" ${OPENSSL_INCLUDE_DIR})

# Link OpenSSL libraries
target_link_libraries(novaledger ${OPENSSL_LIBRARIES})