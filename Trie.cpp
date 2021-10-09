//
// Created by Lenovo on 05.10.2021.
//

#include "Trie.h"


Trie::Trie(std::ifstream &input, std::string file_name) : fin_(input) {
    BitReader reader(fin_);
    std::unordered_map<uint16_t, size_t> freq;
    file_name_ = file_name;
    try {
        while(true) {
            uint16_t symb = reader.ReadBits(8);
            //std::cout << symb << std::endl;
            if (!freq.contains(symb)) {
                freq[symb] = 0;
            }
            freq[symb]++;
        }
    } catch (std::out_of_range) {

    }
    for (char ch : file_name_) {
        uint16_t symb = static_cast<uint16_t>(ch);
        if (!freq.contains(symb)) {
            freq[symb] = 0;
        }
        freq[symb]++;
    }
    Heap queue = Heap();
    for (auto p : freq) {
        queue.insert(new Node(p.second, p.first));
    }
    queue.insert(new Node(1, 256));
    queue.insert(new Node(1, 257));
    queue.insert(new Node(1, 258));
    while(queue.size() >= 2) {
        Node* pt1 = queue.extract();
        Node* pt2 = queue.extract();
        queue.insert(new Node(pt1, pt2));
    }
    root = queue.extract();
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
        increment_vector(cur, cur.size()-1);
        while (cur.size() < p.first) {
            cur.push_back(false);
        }
        res[p.second] = cur;
    }
    return res;
}

/* void Trie::increment_vector(std::vector<bool> &bits, size_t idx) {
    if (bits.empty() || idx >= bits.size()) {
        return;
    }
    if (!bits[idx]) {
        bits[idx] = true;
        return;
    }
    bits[idx] = false;
    if (idx != 0) {
        increment_vector(bits, idx-1);
    }
} */


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