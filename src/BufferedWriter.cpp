//
// Created by valeriahil on 07.06.18.
//

#include <iostream>
#include "BufferedWriter.h"

BufferedWriter::BufferedWriter(std::string const &file) : fout(file, std::ofstream::binary) {}

BufferedWriter::~BufferedWriter() {
    fout.close();
}

void BufferedWriter::add_bit(bool b) {
    cur_char <<= 1;
    cur_char += b;
    rest--;
    if (rest == 0) {
        add_char(cur_char);
        cur_char = 0;
        rest = 8;
    }
}

void BufferedWriter::write_buffer() {
    fout.write(buff, cur_size);
    cur_size = 0;
}

void BufferedWriter::add_char(uint8_t x) {
    if (cur_size == BUFFER_SIZE) {
        write_buffer();
    }
//    buff[cur_size++] = x;
    if (rest == 0) {
        buff[cur_size++] = x;
    } else {
        size_t k = rest;
        cur_char <<= k;
        cur_char += (x >> (8 - k));
        rest = 0;
        add_char(cur_char);
        cur_char = static_cast<uint8_t>(x & ((1 << (8 - k)) - 1));
        rest = k;
    }
}

void BufferedWriter::add_short(uint16_t x) {
    add_char(static_cast<uint8_t>(x >> 8));
    add_char(static_cast<uint8_t>(x & UINT8_MAX));
}

void BufferedWriter::add_vector(std::vector<uint32_t> const &data) {
    for (auto x : data) {
        add_int(x);
    }
}

void BufferedWriter::add_int(uint32_t x) {
    add_short(static_cast<uint16_t>(x >> 16));
    add_short(static_cast<uint16_t>(x & UINT16_MAX));
}

void BufferedWriter::add_code(Code const &code) {
    std::vector<uint32_t> data = code.get_data();
    size_t rest = code.get_rest();

    for (size_t i = 0; i + 1 < data.size(); i++) {
        add_int(data[i]);
    }
    size_t size = 32 - rest;
    while (size >= 8) {
        add_char(static_cast<uint8_t>(data.back() >> (size - 8)));
        data.back() &= ((1 << (size - 8)) - 1);
        size -= 8;
    }

    for (size_t i = 0; i < size; i++) {
        add_bit(static_cast<bool>(data.back() & (1 << (size - i - 1))));
    }
//    for (size_t i = 0; i < code.size(); i++) {
//        add_bit(code.get(i));
//    }
}

void BufferedWriter::check_last() {
    size_t cnt = rest;
    if (rest != 8) {
        for (size_t i = 0; i < cnt; i++) {
            add_bit(0);
        }
    } else {
        cnt = 0;
    }
    add_char(static_cast<uint8_t>(8 - cnt));
    write_buffer();
}

void BufferedWriter::end() {
    write_buffer();
}
