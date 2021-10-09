//
// Created by Lenovo on 05.10.2021.
//

#include "BitReader.h"

BitReader::BitReader(std::ifstream &input) : fin_(input) {
    buffer_size_ = 0;
    buffer_ = 0;
}

bool BitReader::BufferUpdate() {
    if (fin_.eof()) {
        return false;
    }
    while (buffer_size_ + 8 < 30) {
        char x;
        fin_.get(x);
        if (fin_.eof()) {
            return false;
        }
        buffer_ >>= (32 - buffer_size_ - 8);
        buffer_ += static_cast<uint8_t>(x);
        buffer_ <<= (32 - buffer_size_ - 8);
        buffer_size_ += 8;
    }
    return true;
}

uint16_t BitReader::ReadBits(size_t bits) {
    if (bits == 0) {
        return 0;
    }
    while (bits > buffer_size_ && BufferUpdate());
    if (bits > buffer_size_) {
        //std::cerr << "Out of Range ReadBits";
        throw std::out_of_range("Out of Range ReadBits");
    }
    uint16_t res = (buffer_ >> (32 - bits)) << (16 - bits);
    buffer_size_ -= bits;
    buffer_ <<= bits;
    return (res>>(16-bits));
}

bool BitReader::ReadBit() {
    return ReadBits(1);
}

std::vector<bool> BitReader::ReadBitsVector(size_t bits) {
    if (bits == 0) {
        return {};
    }
    uint16_t x = ReadBits(bits);
    std::vector<bool> res;
    for (size_t idx = 0; idx < bits; idx++) {
        res.push_back(x&(1<<(bits-idx-1)));
    }
    return res;
}