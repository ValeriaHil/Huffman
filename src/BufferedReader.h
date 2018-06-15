//
// Created by valeriahil on 07.06.18.
//

#ifndef HAFFMAN_BUFFEREDREADER_H
#define HAFFMAN_BUFFEREDREADER_H

#include <string>
#include <fstream>

struct BufferedReader {
    explicit BufferedReader(std::string const &file);
    ~BufferedReader();
    bool empty();
    void reset();
    uint8_t read_char();
    uint16_t read_short();
    uint32_t read_int();
private:
    static const size_t BUFFER_SIZE = 1024;
    std::ifstream fin;
    size_t pos = 0;
    size_t cur_size = 0;
    char buff[BUFFER_SIZE];

    void read_buffer();
};


#endif //HAFFMAN_BUFFEREDREADER_H
