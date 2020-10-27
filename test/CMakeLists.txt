cmake_minimum_required (VERSION 3.12.4)
project (test)

#
# I use the C++ 17 extensions
# Also, I want warnings treated as errors, and be fairly pedantic
#
set(CMAKE_CXX_STANDARD 17) # C++17...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror")

#
# set default build to debug
#
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#
# Use Conan to download and install all dependencies
#
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#
# Put the binaries into "bin/"
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
include_directories(include ../include)
file(GLOB SOURCES "../src/*.cpp")

add_executable (leetcode ${SOURCES} src/main.cpp)
target_link_libraries(leetcode ${CONAN_LIBS})

