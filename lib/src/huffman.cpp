
#include <iostream>
#include "../include/huffman/huffman.h"

Huffman::Huffman(std::array<uint64_t, 256> const &list_of_cnt) {
    for (size_t i = 0; i < 256; i++) {
        if (list_of_cnt[i] == 0) {
            continue;
        }
        auto x = std::shared_ptr<Node> (new Node(static_cast<uint8_t>(i), list_of_cnt[i]));
        q.push(x);
    }
    build_tree();
}

void Huffman::build_tree() {
    if (q.empty()) {
        return;
    }

    while (q.size() > 1) {
        auto l = q.top();
        q.pop();
        auto r = q.top();
        q.pop();

        auto v = std::shared_ptr<Node>(new Node(l->cnt + r->cnt, l, r));
        q.push(v);
    }
    root = q.top();
    q.pop();
    Code code;
    get_codes(root, code);
}

void Huffman::get_codes(const std::shared_ptr<Huffman::Node> &v, Code &code) {
    if (v == nullptr) {
        return;
    }

    if (v->is_leaf()) {
        if (code.empty()) {
            code.add(0);
            codes[v->data] = code;
            code.pop();
        } else {
            codes[v->data] = code;
        }
        return;
    }

    code.add(0);
    get_codes(v->left, code);
    code.pop();
    code.add(1);
    get_codes(v->right, code);
    code.pop();
}

Huffman::Huffman(std::array<Code, 256> const &codes) {
    this->codes = codes;
    root = std::make_shared<Node>(0, 0);

    for (size_t i = 0; i < 256; i++) {
        Code const &code = codes[i];
        std::shared_ptr<Node> v = root;

        for (size_t k = 0; k < code.size(); k++) {
            bool b = code.get(k);

            if (b) {
                if (v->right == nullptr) {
                    v->right = std::make_shared<Node>(0, 0);
                }
                v = v->right;
            } else {
                if (v->left == nullptr) {
                    v->left = std::make_shared<Node>(0, 0);
                }
                v = v->left;
            }
        }
        v->data = i;
    }
    start();
}

Code &Huffman::encode(uint8_t const &x) {
    return codes[x];
}

Code Huffman::encode(std::vector<uint8_t> const &data) {
    Code code;
    for (auto x : data) {
        code.add(codes[x]);
    }
    return code;
}

void Huffman::start() {
    cur_node = root;

}

void Huffman::go(bool b) {
    if (b) {
        cur_node = cur_node->right;
    } else {
        cur_node = cur_node->left;
    }
}

bool Huffman::is_ready() {
    return cur_node->is_leaf();
}

uint8_t Huffman::get_char() {
    return cur_node->data;
}

std::shared_ptr<Huffman::Node> Huffman::get_cur_node() {
    return cur_node;
}

std::vector<uint8_t> Huffman::decode(char cur, size_t size) {
    std::vector<uint8_t> res;
    if (cur_node == nullptr) {
        cur_node = root;
    }

    for (size_t i = 0; i < size; i++) {
        auto b = static_cast<bool>(cur & (1 << (8 - i - 1)));
        go(b);

        if (get_cur_node() == nullptr) {
            throw std::runtime_error("error");
        }

        if (is_ready()) {
            res.push_back(get_char());
//            writer.add_char(get_char());
            start();
        }
    }
    return res;
}

std::array<Code, 256> &Huffman::get_codes() {
    return codes;
};

