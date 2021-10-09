//
// Created by Lenovo on 06.10.2021.
//

#include "Compress.h"

Compress::Compress(std::string file_name, std::ifstream &input, BitWriter& writer, bool is_end) : fin_(input), writer_(writer) {
    file_name_ = file_name;
    // building codes
    Trie trie = Trie(fin_, file_name_);
    fin_.clear();
    fin_.seekg(0);
    std::vector<std::pair<size_t, uint16_t>> codes = trie.build_codes();
    std::unordered_map<uint16_t, std::vector<bool>> canon = trie.canonize_codes(codes);
    BitReader reader = BitReader(fin_);
    // writing bitcodes for symbols
    writer_.write_from_int(static_cast<uint16_t>(codes.size()), 9);
    for (auto p : codes) {
        writer_.write_from_int(p.second, 9);
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
            counter[p.second.size()]++;
        }
        for (size_t idx = 1; idx <= mx_len; idx++) {
            writer_.write_from_int(counter[idx], 9);
        }
    }
    // writing file name
    for (auto ch : file_name) {
        uint16_t uch = static_cast<uint16_t>(static_cast<uint8_t>(ch));
        writer_.write_bits(canon[uch]);
    }
    writer_.write_bits(canon[FILENAME_END]);
    // writing file
    try {
        while (true) {
            uint16_t x = reader.ReadBits(8);
            writer_.write_bits(canon[x]);
        }
    } catch (...) {

    }

    if (is_end) {
        writer_.write_bits(canon[ARCHIVE_END]);
    } else {
        writer_.write_bits(canon[ONE_MORE_FILE]);
    }

}