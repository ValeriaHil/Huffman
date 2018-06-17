//
// Created by valeriahil on 17.06.18.
//

#include <cstdlib>
#include <string>
#include <array>
#include "huffman/huffman.h"
#include "gtest/gtest.h"

using namespace std;

string res_str(string text) {
    std::array<uint64_t, 256> list_of_cnt{};
    vector<uint8_t> v;
    vector<uint8_t> res;
    string s;

    for (char c : text) {
        v.push_back(static_cast<uint8_t>(c));
        list_of_cnt[v.back()]++;
    }

    Huffman huffman(list_of_cnt);
    Code enc = huffman.encode(v);
    for (size_t i = 0; i < enc.char_size(); i++) {
        size_t cnt;
        char c = enc.get_char(i, cnt);

        vector<uint8_t> cur = huffman.decode(c, cnt);
        for (auto x : cur) {
            res.push_back(x);
        }
    }

    for (char c : res) {
        s += c;
    }
    return s;
}

TEST(correctness, simple) {
    string text = "arget_link_libraries(huffman_lib_testing huffman_lib)\n";
    EXPECT_EQ(text, res_str(text));
}

