//
// Created by valeriahil on 17.06.18.
//

#include <cstdlib>
#include <string>
#include <array>
#include "huffman/huffman.h"
#include "gtest/gtest.h"

using namespace std;


void calc_cnt(vector<uint8_t> const &data, array<uint64_t, 256> &list_of_cnt) {
    for (auto x : data) {
        list_of_cnt[x]++;
    }
}

void encode(vector<uint8_t> const &data, vector<uint8_t> &res, Huffman huffman) {
    Code enc = huffman.encode(data);
    for (size_t i = 0; i < enc.char_size(); i++) {
        size_t cnt;
        char c = enc.get_char(i, cnt);

        vector<uint8_t> cur = huffman.decode(c, cnt);
        for (auto x : cur) {
            res.push_back(x);
        }
    }
}

bool compare(vector<uint8_t> const &a, vector<uint8_t> const &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool check_vector(vector<uint8_t> const &data, vector<uint8_t> &new_data) {
    vector<uint8_t> res_cnt, res_codes;
    std::array<uint64_t, 256> list_of_cnt{};

    calc_cnt(data, list_of_cnt);
    Huffman huffman_cnt(list_of_cnt);
    encode(data, res_cnt, huffman_cnt);
    Huffman huffman_codes(huffman_cnt.get_codes());
    encode(data, res_codes, huffman_codes);


    new_data = res_cnt;
    return compare(data, res_cnt) && compare(data, res_codes);
}

string res_str(string text) {
    vector<uint8_t> v;
    vector<uint8_t> res;
    string s;

    for (char c : text) {
        v.push_back(static_cast<uint8_t>(c));
    }
    check_vector(v, res);
    for (char c : res) {
        s += c;
    }
    return s;
}

TEST(correctness, simple) {
    string text = "target_link_libraries(huffman_lib_testing huffman_lib)\n";
    EXPECT_EQ(text, res_str(text));
}

TEST(correctness, randomize) {
    for (int cnt = 1; cnt < 100; cnt++) {
        auto size = static_cast<size_t>(rand() % 1024);
        vector<uint8_t> v(size);
        vector<uint8_t> new_v(size);
        std::array<uint64_t, 256> list_of_cnt{};

        for (size_t i = 0; i < size; i++) {
            v[i] = static_cast<unsigned char>(rand() % 256);
        }

        EXPECT_EQ(check_vector(v, new_v), true);
    }
}



