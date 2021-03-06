//
// Created by Lenovo on 06.10.2021.
//

#include "BitWriter.h"
#include <vector>
#include <iostream>

BitWriter::BitWriter(std::ofstream &output) : fout_(output) {
    buffer_ = {};
}

void BitWriter::WriteBits(std::vector<bool> &bits) {
    for (auto x : bits) {
        buffer_.push_back(x);
        if (buffer_.size() >= 8) {
            WriteToFile();
        }
    }
}

void BitWriter::WriteFromInt(uint16_t bits, size_t amount) {
    for (size_t idx = 0; idx < amount; ++idx) {
        if (bits & (1 << (amount - idx - 1))) {
            buffer_.push_back(true);
        } else {
            buffer_.push_back(false);
        }
    }
    while (buffer_.size() >= 8) {
        WriteToFile();
    }
}

void BitWriter::WriteToFile() {
    if (buffer_.empty()) {
        fout_.flush();
        return;
    }
    if (buffer_.size() >= 8) {
        uint8_t ch = 0;
        for (size_t idx = 0; idx < 8; ++idx) {
            if (buffer_[idx]) {
                ch |= (1 << (7 - idx));
            }
        }
        buffer_.erase(buffer_.begin(), buffer_.begin() + 8);
        fout_.put(static_cast<char>(ch));
    } else {
        uint8_t ch = 0;
        for (size_t idx = 0; idx < buffer_.size(); ++idx) {
            if (buffer_[idx]) {
                ch |= (1 << (7 - idx));
            }
        }
        buffer_.clear();
        fout_.put(static_cast<char>(ch));
    }
    fout_.flush();
}

BitWriter::~BitWriter() {
    while(!buffer_.empty()){
        WriteToFile();
    }
    fout_.flush();
}