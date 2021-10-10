//
// Created by Lenovo on 05.10.2021.
//

#include "Heap.h"
#include <cstddef>
#include <algorithm>
#include <memory>

Heap::Heap() {
    heap.clear();
}

void Heap::Insert(std::shared_ptr<Node> val) {
    heap.push_back(val);
    SiftUp(heap.size() - 1);
}

void Heap::SiftDown(size_t v) {
    while (2 * v + 1 < heap.size()) {
        size_t left = 2 * v + 1;
        size_t right = 2 * v + 2;
        size_t check = left;
        if (right < heap.size() && (*heap[right]) < (*heap[left])) {
            check = right;
        }
        if ( (*heap[v]) <= (*heap[check])) {
            break;
        }
        std::swap(heap[v], heap[check]);
        v = check;
    }
}

void Heap::SiftUp(size_t v) {
    while (v > 0 && (*heap[v]) < (*heap[(v - 1) / 2])) {
        std::swap(heap[v], heap[(v - 1) / 2]);
        v = (v - 1) / 2;
    }
}

std::shared_ptr<Node> Heap::Extract() {
    if (heap.empty()) {
        return nullptr;
    }
    std::shared_ptr<Node> ret = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    SiftDown(0);
    return ret;
}

bool Heap::empty() const {
    return heap.empty();
}

size_t Heap::size() const {
    return heap.size();
}

