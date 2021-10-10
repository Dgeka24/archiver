//
// Created by Lenovo on 06.10.2021.
//

#include "Compress.h"
#include <string>
#include <algorithm>

Compress::Compress(std::string file_name, std::ifstream &input, BitWriter& writer, bool is_end) : fin_(input), writer_(writer) {
    file_name_ = file_name;
    is_end_ = is_end;
    is_compressed_ = false;
}

void Compress::CompressFile() {
    if (is_compressed_) {
        std::cerr << "Already Compressed";
        return;
    }
    // building codes
    Trie trie = Trie(fin_, file_name_);
    fin_.clear();
    fin_.seekg(0);
    std::vector<std::pair<size_t, uint16_t>> codes = trie.BuildCodes();
    std::unordered_map<uint16_t, std::vector<bool>> canon = trie.CanonizeCodes(codes);
    BitReader reader = BitReader(fin_);
    // writing bitcodes for symbols
    writer_.WriteFromInt(static_cast<uint16_t>(codes.size()), 9);
    for (auto p : codes) {
        writer_.WriteFromInt(p.second, 9);
    }
    // writing amount of symbols with exact bitcode length
    {
        size_t mx_len = 0;
        std::unordered_map<size_t, size_t> counter;
        for (auto p : canon) {
            mx_len = std::max(p.second.size(), mx_len);
            if (!counter.contains(p.second.size())) {
                counter[p.second.size()] = 0;
            }
            ++counter[p.second.size()];
        }
        for (size_t idx = 1; idx <= mx_len; ++idx) {
            writer_.WriteFromInt(counter[idx], 9);
        }
    }
    // writing file name
    for (auto ch : file_name_) {
        uint16_t uch = static_cast<uint16_t>(static_cast<uint8_t>(ch));
        writer_.WriteBits(canon[uch]);
    }
    writer_.WriteBits(canon[FILENAME_END]);
    // writing file
    try {
        while (true) {
            uint16_t x = reader.ReadBits(8);
            writer_.WriteBits(canon[x]);
        }
    } catch (...) {

    }
    if (is_end_) {
        writer_.WriteBits(canon[ARCHIVE_END]);
    } else {
        writer_.WriteBits(canon[ONE_MORE_FILE]);
    }
    is_compressed_ = true;
}