//
// Created by valeriahil on 07.06.18.
//

#include "BufferedReader.h"

BufferedReader::BufferedReader(std::string const &file) : fin(file, std::ifstream::binary)  {
    if (fin.fail()) {
        fin.close();
        throw std::runtime_error("Can't read file " + file);
    }
}

BufferedReader::~BufferedReader() {
    fin.close();
}

bool BufferedReader::empty() {
    if (pos == cur_size) {
        read_buffer();
    }
    return cur_size == 0;
}

void BufferedReader::reset() {
    pos = 0;
    cur_size = 0;
    fin.clear();
    fin.seekg(0, std::ios_base::beg);
    read_buffer();
}

void BufferedReader::read_buffer() {
    fin.read(buff, BUFFER_SIZE);
    cur_size = static_cast<size_t>(fin.gcount());
    pos = 0;
}

uint8_t BufferedReader::read_char() {
    if (empty()) {
        throw std::runtime_error("Unexpected end of file");
    }
    return static_cast<uint8_t>(buff[pos++]);
}

uint16_t BufferedReader::read_short() {
    uint16_t res = read_char();
    res <<= 8;
    res += read_char();
    return res;
}

uint32_t BufferedReader::read_int() {
    uint32_t res = read_short();
    res <<= 16;
    res += read_short();
    return res;
}
