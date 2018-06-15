//
// Created by valeriahil on 07.06.18.
//

#ifndef HAFFMAN_BUFFEREDWRITER_H
#define HAFFMAN_BUFFEREDWRITER_H

#include <string>
#include <fstream>
#include <vector>
#include "../lib/Code.h"

struct BufferedWriter {
    explicit BufferedWriter(std::string const &file);
    ~BufferedWriter();

    void add_bit(bool b);
    void add_char(uint8_t x);
    void add_short(uint16_t x);
    void add_int(uint32_t x);
    void add_code(Code const &code);
    void add_vector(std::vector<uint32_t> const &data);
    void check_last();
    void end();

private:
    static const size_t BUFFER_SIZE = 1024;
    char buff[BUFFER_SIZE];
    size_t cur_size = 0;
    size_t rest = 8;
    uint8_t cur_char = 0;
    std::ofstream fout;

    void write_buffer();
};


#endif //HAFFMAN_BUFFEREDWRITER_H
