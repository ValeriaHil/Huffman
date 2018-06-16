#ifndef HAFFMAN_HAFFMAN_H
#define HAFFMAN_HAFFMAN_H

#include <memory>
#include <utility>
#include <vector>
#include <queue>
#include "Code.h"

struct Huffman {
    explicit Huffman(std::array<uint64_t, 256> list_of_cnt);

    explicit Huffman(std::array<Code, 256> const &codes);

    Code &encode(uint8_t const &x);

private:
    struct Node {
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        uint8_t data;
        uint64_t cnt;

        Node(uint8_t c, uint64_t cnt) : left(nullptr), right(nullptr), data(c), cnt(cnt) {}

        Node(uint8_t cnt, std::shared_ptr<Node> l, std::shared_ptr<Node> r) : left(std::move(l)), right(std::move(r)),
                                                                              cnt(cnt) {}

        inline bool is_leaf() {
            return left == right && left == nullptr;
        }
    };


    std::shared_ptr<Node> root = nullptr;

    struct comp {
        bool operator()(std::shared_ptr<Node> const &l, std::shared_ptr<Node> const &r) {
            return l->cnt > r->cnt;
        }
    };

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, comp> q;

    void build_tree();

    std::array<Code, 256> codes;

    void get_codes(std::shared_ptr<Node> const &v, Code &code);

    std::shared_ptr<Node> cur_node;

public:
    void start();

    void go(bool b);

    bool is_ready();

    uint8_t get_char();

    std::shared_ptr<Node> get_cur_node();
};

#endif //HAFFMAN_HAFFMAN_H
