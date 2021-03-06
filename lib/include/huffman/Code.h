//
// Created by valeriahil on 05.06.18.
//

#ifndef HAFFMAN_CODE_H
#define HAFFMAN_CODE_H


#include <cstdint>
#include <vector>

struct Code {
    Code();
    Code(std::vector<uint32_t> const &data, size_t const &rest);
    void add(bool b);
    void add(Code& code);
    void pop();
    bool empty() const;
    size_t size() const;
    size_t char_size() const;
    bool get(size_t ind) const;
    uint8_t get_char(size_t ind, size_t &char_size) const;
    size_t get_rest()const;
    std::vector<uint32_t> const &get_data() const;

private:
    std::vector<uint32_t> data;
    size_t rest = 0;
};


#endif //HAFFMAN_CODE_H
