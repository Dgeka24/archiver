//
// Created by Lenovo on 06.10.2021.
//

#include "Compress.h"

Compress::Compress(std::string file_name, std::ifstream &input, std::ofstream &output) : fin_(input), fout_(output) {

    Trie trie = Trie(fin_);
    fin_.clear();
    fin_.seekg(0);
    std::vector<std::pair<size_t, uint16_t>> codes = trie.build_codes();
    std::unordered_map<uint16_t, std::vector<bool>> canon = trie.canonize_codes(codes);
    BitWriter writer = BitWriter(fout_);
    BitReader reader = BitReader(fin_);
    writer.write_from_int(static_cast<uint16_t>(codes.size()), 9);
    for (auto p : codes) {
        writer.write_from_int(p.second, 9);
    }
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
        for (size_t idx = 0; idx < mx_len; idx++) {
            writer.write_from_int(counter[idx], 9);
        }
    }





}