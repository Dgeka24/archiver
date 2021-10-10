//
// Created by Lenovo on 08.10.2021.
//
#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "BitReader.h"
#include "Trie.h"
#include <iostream>
#include "CONSTANTS.h"
#include "BitWriter.h"

class Decompress {
public:
    Decompress(std::string archive_name);
    void DecompressArchive();

private:
    std::string archive_name_;
    std::ifstream fin_;
    std::unordered_map<std::vector<bool>, uint16_t> codes_;
    BitReader reader_;
    bool is_decompressed_ = false;
    bool Decompress_file();
    void build_codes();
    std::string read_file_name();
};