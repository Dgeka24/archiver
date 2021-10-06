cmake_minimum_required(VERSION 3.20)
project(archiever)

set(CMAKE_CXX_STANDARD 20)

add_executable(archiever main.cpp BitReader.cpp BitReader.h Heap.cpp Heap.h Trie.cpp Trie.h Node.cpp BitWriter.cpp BitWriter.h Compress.cpp Compress.h)
