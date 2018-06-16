//
// Created by valeriahil on 05.06.18.
//

#include <iostream>
#include <array>
#include "BufferedReader.h"
#include "../../lib/include/huffman/huffman.h"
#include "BufferedWriter.h"


using namespace std;

void write_dict(Huffman &haffman, BufferedWriter &writer) {
    for (size_t i = 0; i < 256; i++) {
        Code &code = haffman.encode(static_cast<const uint8_t &>(i));
        auto const &data = code.get_data();
        writer.add_short(static_cast<uint16_t>(data.size()));
        if (!data.empty()) {
            writer.add_char(static_cast<uint8_t>(code.get_rest()));
            writer.add_vector(data);
        }
    }
}

void encode(Huffman &haffman, BufferedReader &reader, BufferedWriter &writer) {
    write_dict(haffman, writer);

    while (!reader.empty()) {
        Code &code = haffman.encode(reader.read_char());
        writer.add_code(code);
    }
    writer.check_last();
}

void decode_dict(BufferedReader &reader, std::array<Code, 256> &codes) {
    for (size_t i = 0; i < 256; i++) {
        uint16_t data_size = reader.read_short();
        if (data_size) {
            uint8_t rest = reader.read_char();
            std::vector<uint32_t> v;
            for (size_t j = 0; j < data_size; j++) {
                v.push_back(reader.read_int());
            }
            codes[i] = Code(v, rest);
        }
    }
}

void decode(BufferedReader &reader, BufferedWriter &writer) {
    std::array<Code, 256> codes;
    decode_dict(reader, codes);
    Huffman haffman(codes);

    uint8_t cur = reader.read_char();
    while (!reader.empty()) {
        uint8_t nxt = reader.read_char();
        size_t cnt = 8;
        if (reader.empty()) {
            cnt = nxt;
        }
        writer.add_vector(haffman.decode(cur, cnt));
        cur = nxt;
    }
    writer.end();
}

int main(int args, char *argv[]) {
    if (args < 4) {
        printf("Wrong number of args\n");
        return 0;
    }

    string mode = argv[1];
    string src = argv[2];
    string dst = argv[3];
    if (mode != "-e" && mode != "-d") {
        printf("Wrong mode\n");
        return 0;
    }

    try {
        BufferedReader reader(src);
        BufferedWriter writer(dst);

        if (mode == "-e") {
            std::array<uint64_t, 256> list_of_cnt{};
            while (!reader.empty()) {
                list_of_cnt[reader.read_char()]++;
            }
            reader.reset();
            Huffman haffman(list_of_cnt);
            encode(haffman, reader, writer);
        } else {
            decode(reader, writer);
        }

    } catch (std::exception &e) {
        printf("%s ", e.what());
    }
    return 0;
}