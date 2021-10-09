//
// Created by Lenovo on 06.10.2021.
//

#pragma once
#include <string>
#include <fstream>
#include "Trie.h"
#include "BitWriter.h"
#include "BitReader.h"
#include <algorithm>
#include "CONSTANTS.h"

#ifndef ARCHIEVER_COMPRESS_H
#define ARCHIEVER_COMPRESS_H


class Compress {
public:
    Compress(std::string file_name, std::ifstream &input, BitWriter& writer, bool is_end);
private:
    std::string file_name_;
    std::ifstream& fin_;
    BitWriter& writer_;
};


#endif //ARCHIEVER_COMPRESS_H
