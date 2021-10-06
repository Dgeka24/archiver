#include <iostream>
#include <fstream>
#include "BitReader.h"
#include "Trie.h"
#include "BitWriter.h"
#include "Compress.h"

int main() {
    // ошибка с чтением написанием битов в файл
    std::ifstream fin("input.txt", std::fstream::binary);
    BitReader reader = BitReader(fin);
    try {
        while (true) {
            uint16_t x = reader.ReadBits(9);
            std::cout << x << std::endl;
        }
    } catch (...) {
        std::cout << "EOF";
    }

    return 0;

    //std::ifstream fin("input.txt", std::fstream::binary);
    std::ofstream fout("output.txt", std::fstream::binary);
    if (!fout.is_open()) {
        std::cerr << "file didn't open";
        throw;
    }

    if (!fin.is_open())
    {
        std::cerr << "file didn't open\n";
        throw;
    }

    Compress cmp = Compress("input.txt", fin, fout);


    return 0;
    char x;
    Trie t(fin);
    std::vector<std::pair<size_t, uint16_t>> res = t.build_codes();
    for (auto x : res) {
        std::cout << x.first << " : " << x.second;
        std::cout << "\n";
    }
    std::unordered_map<uint16_t, std::vector<bool>> canon = t.canonize_codes(res);
    for (auto x : canon) {
        std::cout << x.first << " : ";
        for (auto y : x.second) {
            std::cout << y << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
