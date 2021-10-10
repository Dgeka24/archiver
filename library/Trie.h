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
#include <memory>

class Trie {
public:
    Trie(std::ifstream& input, std::string file_name = "");
    void BuildCodes(std::shared_ptr<Node> v, std::vector<bool>& current, std::vector<std::pair<size_t, uint16_t>>& res);
    std::vector<std::pair<size_t, uint16_t>> BuildCodes();
    std::unordered_map<uint16_t, std::vector<bool>> CanonizeCodes(std::vector<std::pair<size_t, uint16_t>>& codes);

    static void IncrementVector(std::vector<bool>& bits, size_t idx, size_t length) {
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
                IncrementVector(bits, idx - 1, 0);
            }
        }
        while (bits.size() < length) {
            bits.push_back(false);
        }
    }
private:
    std::shared_ptr<Node> BuildTrie();
    std::shared_ptr<Node> root = nullptr;
    std::ifstream& fin_;
    std::string file_name_;
};


