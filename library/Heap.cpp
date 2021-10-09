//
// Created by Lenovo on 05.10.2021.
//

#include "Heap.h"

Heap::Heap() {
    heap.clear();
}

void Heap::insert(Node* val) {
    heap.push_back(val);
    sift_up(heap.size() - 1);
}

void Heap::sift_down(size_t v) {
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

void Heap::sift_up(size_t v) {
    while (v > 0 && (*heap[v]) < (*heap[(v - 1) / 2])) {
        std::swap(heap[v], heap[(v - 1) / 2]);
        v = (v - 1) / 2;
    }
}

Node* Heap::extract() {
    if (heap.empty()) {
        //std::cerr << "empty heap" << std::endl;
        return nullptr;
    }
    Node* ret = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    sift_down(0);
    return ret;
}

bool Heap::empty() {
    return heap.empty();
}

size_t Heap::size() {
    return heap.size();
}

