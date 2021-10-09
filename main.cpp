#include <iostream>
#include <fstream>
#include "BitReader.h"
#include "Trie.h"
#include "BitWriter.h"
#include "Compress.h"
#include "Decompress.h"

int main(int argc, char* argv[]) {

    /*std::string picture_path = "C:\\Users\\Lenovo\\Downloads\\1556945414_2.jpg";
    std::ifstream fin(picture_path, std::fstream::binary);
    if (!fin.is_open()){
        return 5;
    }
    std::ofstream fout("output.txt", std::fstream::binary);
    Compress cmp = Compress(picture_path, fin, fout, true);*/
    Decompress decomp = Decompress("output.txt");

}
