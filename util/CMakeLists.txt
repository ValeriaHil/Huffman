
add_executable(huffman
        src/main.cpp
        src/BufferedReader.cpp
        src/BufferedWriter.cpp
        )

target_link_libraries(huffman libhuffman)