//
// Created by Lenovo on 05.10.2021.
//
#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class BitReader {
public:
    BitReader(std::ifstream& input);
    uint16_t ReadBits(size_t bits);
    std::vector<bool> ReadBitsVector(size_t bits);
    bool ReadBit();
private:
    bool BufferUpdate();
    uint32_t buffer_;
    uint32_t buffer_size_;
    std::ifstream& fin_;
    size_t counter = 0;
};