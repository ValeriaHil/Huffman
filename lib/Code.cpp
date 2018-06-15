//
// Created by valeriahil on 05.06.18.
//

#include "Code.h"

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
}

bool Code::empty() {
    return data.empty();
}

size_t Code::size() const {
    return 32 * data.size() - rest;
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

void Code::add(Code &code) {
    for (size_t i = 0; i < code.size(); i++) {
        add(code.get(i));
    }
}

std::vector<uint32_t> Code::get_data() {
    return data;
}

size_t Code::get_rest() {
    return rest;
}

Code::Code(std::vector<uint32_t> const &data, size_t const &rest) : data(data), rest(rest){}
