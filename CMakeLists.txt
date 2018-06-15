cmake_minimum_required(VERSION 3.9)
project(haffman)

set(CMAKE_CXX_STANDARD 11)

include_directories(${HAFFMAN_SOURCE_DIR})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(testing gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc testing.cpp
        lib/huffman.h lib/huffman.cpp
        lib/Code.cpp lib/Code.h)

add_executable(haffman lib/huffman.h lib/huffman.cpp
        lib/Code.cpp lib/Code.h src/main.cpp src/BufferedReader.cpp src/BufferedReader.h src/BufferedWriter.cpp src/BufferedWriter.h)

target_link_libraries(testing -lpthread)