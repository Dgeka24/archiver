//
// Created by Lenovo on 05.10.2021.
//

#include "Trie.h"
#include <stdint.h>
#include <iostream>
#include <unordered_map>


Trie::Trie(std::ifstream &input, std::string file_name) : fin_(input) {
    file_name_ = std::move(file_name);
    root = BuildTrie();
}

Node* Trie::BuildTrie() {
    BitReader reader(fin_);
    std::unordered_map<uint16_t, size_t> freq;
    try {
        while(true) {
            uint16_t symb = reader.ReadBits(8);
            if (!freq.contains(symb)) {
                freq[symb] = 0;
            }
            freq[symb]++;
        }
    } catch (std::out_of_range) {

    }
    for (char ch : file_name_) {
        uint16_t symb = static_cast<uint16_t>(static_cast<uint8_t>(ch));
        if (!freq.contains(symb)) {
            freq[symb] = 0;
        }
        freq[symb]++;
    }
    Heap queue = Heap();
    for (auto p : freq) {
        queue.insert(new Node(p.second, p.first));
    }
    queue.insert(new Node(1, FILENAME_END));
    queue.insert(new Node(1, ONE_MORE_FILE));
    queue.insert(new Node(1, ARCHIVE_END));
    while(queue.size() >= 2) {
        Node* pt1 = queue.extract();
        Node* pt2 = queue.extract();
        queue.insert(new Node(pt1, pt2));
    }
    root = queue.extract();
    return root;
}

std::vector<std::pair<size_t, uint16_t>> Trie::build_codes() {
    std::vector<bool> current = {};
    std::vector<std::pair<size_t, uint16_t>> res;
    build_codes(root, current, res);
    std::sort(res.begin(), res.end());
    return res;
}

std::unordered_map<uint16_t, std::vector<bool>> Trie::canonize_codes(std::vector<std::pair<size_t, uint16_t>> &codes) {
    std::unordered_map<uint16_t, std::vector<bool>> res;
    std::vector<bool> cur;
    for (auto p : codes) {
        increment_vector(cur, cur.size() - 1, p.first);
        res[p.second] = cur;
    }
    return res;
}

void Trie::build_codes(Node* v, std::vector<bool> &current, std::vector<std::pair<size_t, uint16_t>>& res) {
    if (!v->left && !v->right) {
        res.push_back({current.size(), v->key});
        return;
    }
    if (v->left) {
        current.push_back(false);
        build_codes(v->left, current, res);
        current.pop_back();
    }
    if (v->right) {
        current.push_back(true);
        build_codes(v->right, current, res);
        current.pop_back();
    }
}

Trie::~Trie() {
    dfs(root);
}

void Trie::dfs(Node* v) {
    if (!v) {
        return;
    }
    if (v->left) {
        dfs(v->left);
    }
    if (v->right) {
        dfs(v->right);
    }
    delete v;
}