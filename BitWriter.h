//
// Created by Lenovo on 06.10.2021.
//
#pragma once
#include <vector>
#include <iostream>
#include <fstream>

#ifndef ARCHIEVER_BITWRITER_H
#define ARCHIEVER_BITWRITER_H

class BitWriter {
public:
    ~BitWriter();
    BitWriter(std::ofstream& output);
    void write_bits(std::vector<bool> &bits);
    void write_from_int(uint16_t bits, size_t amount);
    void write_to_file();

private:
    std::ofstream& fout_;
    std::vector<bool> buffer_;
};


#endif //ARCHIEVER_BITWRITER_H
