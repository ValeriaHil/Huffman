add_library(libhuffman
        src/huffman.cpp
        src/Code.cpp)

target_include_directories(libhuffman
       PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
       PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(testlib
        tests/gtest/gtest-all.cc
        tests/gtest/gtest_main.cc)

target_link_libraries(testlib
        libhuffman
        -lpthread)