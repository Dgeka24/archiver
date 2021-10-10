//
// Created by Lenovo on 05.10.2021.
//
#pragma once
#include <cstddef>
#include <algorithm>
#include <vector>
#include "Trie.h"
#include <iostream>
#include "Node.cpp"


class Heap {
public:
    Heap();
    void insert(Node* val);
    void sift_down(size_t v);
    void sift_up(size_t v);
    Node* extract();
    bool empty() const;
    size_t size() const;

private:
    std::vector<Node*> heap;
};



