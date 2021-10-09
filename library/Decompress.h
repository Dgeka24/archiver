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

#ifndef ARCHIEVER_DECOMPRESS_H
#define ARCHIEVER_DECOMPRESS_H


class Decompress {
public:
    Decompress(std::string archive_name);
    bool Decompress_file();

private:
    std::string archive_name_;
    std::ifstream fin_;
    std::unordered_map<std::vector<bool>, uint16_t> codes_;
    BitReader reader_;

    void build_codes();
    std::string read_file_name();
};


#endif //ARCHIEVER_DECOMPRESS_H
