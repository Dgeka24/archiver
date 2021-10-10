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
#include <memory>


class Heap {
public:
    Heap();
    void Insert(std::shared_ptr<Node> val);
    void SiftDown(size_t v);
    void SiftUp(size_t v);
    std::shared_ptr<Node> Extract();
    bool empty() const;
    size_t size() const;

private:
    std::vector<std::shared_ptr<Node>> heap;
};



