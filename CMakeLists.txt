cmake_minimum_required(VERSION 3.20)
project(archiever)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)

add_executable(archiever main.cpp library/BitReader.cpp library/BitReader.h library/Heap.cpp library/Heap.h library/Trie.cpp library/Trie.h library/Node.cpp library/BitWriter.cpp library/BitWriter.h library/Compress.cpp library/Compress.h library/CONSTANTS.h library/Decompress.cpp library/Decompress.h)
