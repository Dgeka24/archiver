#include "../library/BitReader.h"
#include "../library/BitReader.cpp"
#include "../library/BitWriter.h"
#include "../library/BitWriter.cpp"
#include "../library/Compress.h"
#include "../library/Compress.cpp"
#include "../library/Decompress.h"
#include "../library/Decompress.cpp"
#include "../library/CONSTANTS.h"
#include "../library/Heap.h"
#include "../library/Heap.cpp"
#include "../library/Node.cpp"
#include "../library/Trie.h"
#include "../library/Trie.cpp"
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("TestCompessAndDecompress") {
    std::string test_text1 = "People’s lives don’t end when they die, it ends when they lose faith. -Itachi Uchiha";
    std::string test_text2 = "I met the girl under full-bloomed cherry blooms, and my fate has begun to change";
    std::string file_name1 = "check_compress1.txt";
    std::string file_name2 = "check_compress2.txt";
    std::ofstream output1(file_name1, std::fstream::binary);
    std::ofstream output2(file_name2, std::fstream::binary);
    for (auto &ch : test_text1) {
        output1.put(ch);
    }
    for (auto &ch : test_text2) {
        output2.put(ch);
    }
    output1.close();
    output2.close();

    std::ifstream input1(file_name1, std::fstream::binary);
    std::ifstream input2(file_name2, std::fstream::binary);
    std::string archive_name = "archive.txt";
    std::ofstream output_archive(archive_name, std::fstream::binary);
    BitWriter writer(output_archive);
    Compress cmp1 = Compress(file_name1, input1, writer, false);
    cmp1.CompressFile();
    Compress cmp2 = Compress(file_name2, input2, writer, true);
    cmp2.CompressFile();
    input1.close();
    input2.close();
    output_archive.close();
    Decompress dcmp(archive_name);
    dcmp.DecompressArchive();
    input1 = std::ifstream(file_name1, std::fstream::binary);
    input2 = std::ifstream(file_name2, std::fstream::binary);
    std::string text1;
    std::string text2;
    while(!input1.eof()) {
        char ch = input1.get();
        if (input1.eof()) {
            break;
        }
        text1 += ch;
    }
    while(!input2.eof()) {
        char ch = input2.get();
        if (input2.eof()) {
            break;
        }
        text2 += ch;
    }
    REQUIRE(text1 == test_text1);
    REQUIRE(text2 == test_text2);

}

TEST_CASE("TestBitReaderAndBitWriter") {
    std::ofstream output("check_reading.txt", std::fstream::binary);
    {
        BitWriter writer(output);
        writer.WriteFromInt(static_cast<uint8_t>(0b10101010), 8);
        writer.WriteFromInt(0b111, 3);
        std::vector<bool> to_write = {true, true, true, true, true};
        writer.WriteBits(to_write);
    }
    output.close();
    std::ifstream input("check_reading.txt", std::fstream::binary);
    BitReader reader(input);
    std::vector<bool> cur = reader.ReadBitsVector(1);
    std::vector<bool> wanted = {true};
    REQUIRE(cur == wanted);
    cur = reader.ReadBitsVector(3);
    wanted = {false, true, false};
    REQUIRE(cur == wanted);
    cur = reader.ReadBitsVector(4);
    wanted = {true, false, true, false};
    REQUIRE(cur == wanted);
    uint16_t x = reader.ReadBits(8);
    uint16_t y = 255;
    REQUIRE(x == y);
}