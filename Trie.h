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



class Trie {
public:
    ~Trie();
    Trie(std::ifstream& input);

    void build_codes(Node* v, std::vector<bool>& current, std::vector<std::pair<size_t, uint16_t>> &res);
    std::vector<std::pair<size_t, uint16_t>> build_codes();
    std::unordered_map<uint16_t, std::vector<bool>> canonize_codes(std::vector<std::pair<size_t, uint16_t>> &codes);
    void increment_vector(std::vector<bool> &bits, size_t idx);
private:
    void dfs(Node* v);
    Node* root = nullptr;
    std::ifstream& fin_;

};


