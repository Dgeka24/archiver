//
// Created by Lenovo on 06.10.2021.
//
#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class BitWriter {
public:
    ~BitWriter();
    BitWriter(std::ofstream& output);
    void WriteBits(std::vector<bool> &bits);
    void WriteFromInt(uint16_t bits, size_t amount);
    void WriteToFile();

private:
    std::ofstream& fout_;
    std::vector<bool> buffer_;
};