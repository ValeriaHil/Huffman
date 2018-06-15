//
// Created by valeriahil on 04.06.18.
//
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include "gtest/gtest.h"

#include "lib/huffman.h"
#include "gtest/gtest.h"

TEST(correctness, haffman)
{
    std::array<uint64_t, 256> a{};
    for (size_t i = 0; i < 5; i++) {
        a[i] = i;
    }
    Huffman h(a);
    for (size_t i = 0; i < 5; i++) {
        Code const &code = h.codes[i];
        for (size_t k = 0; k < code.size(); k++) {
            bool b = code.get(k);
            std::cout << b << std::endl;
        }
        std::cout << "-----" << std::endl;
    }
}
