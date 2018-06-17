//
// Created by valeriahil on 05.06.18.
//

#include "../include/huffman/Code.h"

Code::Code() : data(0), rest(0) {}

void Code::add(bool b) {
    if (rest == 0) {
        data.push_back(b);
        rest = 31;
        return;
    }
    rest--;
    data.back() <<= 1;
    data.back() += b;
}

void Code::pop() {
    if (rest == 31) {
        data.pop_back();
        rest = 0;
        return;
    }
    data.back() >>= 1;
    rest++;
    if (rest == 32) {
        data.pop_back();
        rest = 0;
    }
}

bool Code::empty() const {
    return data.empty();
}

size_t Code::size() const {
    return 32 * data.size() - rest;
}

size_t Code::char_size() const {
    return 4 * data.size();
}

bool Code::get(size_t ind) const {
    size_t block = ind / 32;
    ind %= 32;
    if (block + 1 != data.size()) {
        return static_cast<bool>(data[block] & (1 << (31 - ind)));
    } else {
        return static_cast<bool>(data[block] & (1 << ((31 - rest - ind))));
    }
}

uint8_t Code::get_char(size_t ind, size_t &char_size) const {
    size_t block = ind / 4;
    ind %= 4;
    uint32_t res = (data[block]);
    char_size = 8;
    if (block + 1 == data.size()) {
        res <<= rest;
    }
    if (ind == 0) {
        res >>= 24;
        if (rest > 24 && block + 1 == data.size()) {
            char_size = 8 - (rest - 24);
        }
    }
    if (ind == 1) {
        res >>= 16;
        res &= UINT8_MAX;
        if (block + 1 == data.size()) {
            if (rest > 16) {
                if (rest > 24) {
                    char_size = 0;
                } else {
                    char_size = 8 - (rest - 16);
                }
            }
        }
    }
    if (ind == 2) {
        res &= UINT16_MAX;
        res >>= 8;
        if (rest > 8 && block + 1 == data.size()) {
            if (rest > 16) {
                char_size = 0;
            } else {
                char_size = 8 - (rest - 8);
            }
        }
    }
    if (ind == 3) {
        res &= UINT8_MAX;
        if (rest && block + 1 == data.size()) {
            if (rest > 8) {
                char_size = 0;
            } else {
                char_size = 8 - rest;
            }
        }
    }

    return static_cast<uint8_t>(res);
}

void Code::add(Code &code) {
    for (size_t i = 0; i < code.size(); i++) {
        add(code.get(i));
    }
}

std::vector<uint32_t> const &Code::get_data() const {
    return data;
}

size_t Code::get_rest() const {
    return rest;
}

Code::Code(std::vector<uint32_t> const &data, size_t const &rest) : data(data), rest(rest) {}
