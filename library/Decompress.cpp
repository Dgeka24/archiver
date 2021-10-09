//
// Created by Lenovo on 08.10.2021.
//

#include "Decompress.h"

Decompress::Decompress(std::string archive_name) : fin_(std::ifstream(archive_name, std::fstream::binary)), reader_(fin_) {
    archive_name_ = archive_name;
    while (Decompress_file());
}

bool Decompress::Decompress_file() {
    codes_.clear();
    build_codes();
    std::string file_name = read_file_name();
    std::ofstream output(file_name, std::fstream::binary);
    BitWriter writer = BitWriter(output);
    std::vector<bool> cur;
    while (true) {
        cur.push_back(reader_.ReadBit());
        if (codes_.contains(cur)) {
            uint16_t symbol = codes_[cur];
            if (symbol == ONE_MORE_FILE) {
                return true;
            } else if (symbol == ARCHIVE_END) {
                return false;
            } else {
                writer.write_from_int(symbol, 8);
            }
            cur.clear();
        }
    }
}



std::string Decompress::read_file_name() {
    std::vector<bool> cur;
    std::string file_name;
    while (true) {
        cur.push_back(reader_.ReadBit());
        if (codes_.contains(cur)) {
            uint16_t symbol = codes_[cur];
            if (symbol == FILENAME_END) {
                return file_name;
            } else {
                file_name += static_cast<char>(static_cast<uint8_t>(symbol));
            }
            cur.clear();
        }
    }
}


void Decompress::build_codes() {
    uint16_t symbols_count = reader_.ReadBits(9);
    std::vector<uint16_t> symbols_in_canon_order(symbols_count);
    for (uint16_t& ch : symbols_in_canon_order) {
        ch = reader_.ReadBits(9);
    }
    std::vector<size_t> amount_of_exact_length;
    amount_of_exact_length.push_back(0);
    while (symbols_count) {
        uint16_t amount = reader_.ReadBits(9);
        symbols_count -= amount;
        amount_of_exact_length.push_back(amount);
    }
    std::vector<bool> cur;
    size_t idx_of_cur_symbol = 0;
    for (size_t length = 1; length < amount_of_exact_length.size(); length++) {
        while (amount_of_exact_length[length] > 0) {
            Trie::increment_vector(cur, cur.size() - 1);
            while (cur.size() < length) {
                cur.push_back(false);
            }
            codes_[cur] = symbols_in_canon_order[idx_of_cur_symbol];
            idx_of_cur_symbol++;
            amount_of_exact_length[length]--;
        }
    }
}
