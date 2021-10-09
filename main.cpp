#include <iostream>
#include <fstream>
#include "BitReader.h"
#include "Trie.h"
#include "BitWriter.h"
#include "Compress.h"
#include "Decompress.h"
#include <algorithm>
#include <filesystem>
#include <cstring>


void CompressFiles(int argc, char* argv[]) {
    std::string archive_name = argv[2];
    std::ofstream output(archive_name, std::fstream::binary);
    if (!output.is_open()) {
        throw std::runtime_error("No archive file found");
    }
    BitWriter writer(output);
    size_t last_idx = 2;
    for (size_t idx = 3; idx < argc; idx++) {
        std::string file_name = argv[idx];
        if (std::filesystem::exists(file_name)) {
            last_idx = std::max(last_idx, idx);
        }
    }
    if (last_idx == 2) {
        throw std::runtime_error("No files for archiving found");
    }
    for (size_t idx = 3; idx < last_idx; idx++) {
        std::string file_name = argv[idx];
        std::ifstream input(file_name, std::fstream::binary);
        if (input.is_open()) {
            Compress cmp = Compress(file_name, input, writer, false);
        }
    }
    std::string file_name = argv[last_idx];
    std::ifstream input(file_name, std::fstream::binary);
    Compress cmp = Compress(file_name, input, writer, true);
}

void DecompressFiles(char* argv[]) {
    std::string archive_name = argv[2];
    if (!std::filesystem::exists(archive_name)) {
        throw std::runtime_error("No archive file found");
    }
    Decompress dcmp(archive_name);
}

void PrintHelp() {
    std::cout << "Call a program with arguments: -c archive_name file1 [file2 ...] to compress files into archive_name"
              << std::endl;
    std::cout << "Call a program with arguments: archiver -d archive_name to decompress files" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc == 1){
        std::cout << "No arguments found!";
        return 1;
    } else {
        if (std::strcmp(argv[1], "-h") == 0) {
            PrintHelp();
        } else if (std::strcmp(argv[1], "-c") == 0) {
            if (argc < 4) {
                std::cout << "Wrong arguments";
                return 1;
            }
            CompressFiles(argc, argv);
        } else if (std::strcmp(argv[1], "-d") == 0) {
            if (argc != 3) {
                std::cout << "Wrong arguments";
                return 1;
            }
            DecompressFiles(argv);
        } else {
            std::cout << "Wrong arguments";
            return 1;
        }
    }

}
