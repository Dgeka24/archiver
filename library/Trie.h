//
// Created by Lenovo on 05.10.2021.
//
#pragma once
#include <cstddef>
#include <stdint.h>
#include <iostream>
#include <unordered_map>
#include "BitReader.h"
#include "Heap.h"
#include "Node.cpp"
#include "CONSTANTS.h"

class Trie {
public:
    ~Trie();
    Trie(std::ifstream& input, std::string file_name = "");

    void build_codes(Node* v, std::vector<bool>& current, std::vector<std::pair<size_t, uint16_t>> &res);
    std::vector<std::pair<size_t, uint16_t>> build_codes();
    std::unordered_map<uint16_t, std::vector<bool>> canonize_codes(std::vector<std::pair<size_t, uint16_t>> &codes);

    static void increment_vector(std::vector<bool> &bits, size_t idx, size_t length) {
        if (bits.empty() || idx >= bits.size()) {
            while (bits.size() < length) {
                bits.push_back(false);
            }
            return;
        }
        if (!bits[idx]) {
            bits[idx] = true;
        } else {
            bits[idx] = false;
            if (idx != 0) {
                increment_vector(bits, idx-1, 0);
            }
        }
        while (bits.size() < length) {
            bits.push_back(false);
        }
    }
private:
    void dfs(Node* v);
    Node* BuildTrie();
    Node* root = nullptr;
    std::ifstream& fin_;
    std::string file_name_;
};


