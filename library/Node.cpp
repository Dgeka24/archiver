//
// Created by Lenovo on 06.10.2021.
//
#pragma once
#include <cstdint>
#include <memory>

struct Node {
    size_t val = 0;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    uint16_t key = 0;
    Node(size_t val_, uint16_t key_) {
        val = val_;
        key = key_;
        left = nullptr;
        right = nullptr;
    }
    Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        val = left->val + right->val;
        key = 0;
        this->left = left;
        this->right = right;
    }
    bool operator<(const Node& b) const {
        return val < b.val;
    }
    bool operator>(const Node& b) const {
        return val > b.val;
    }
    bool operator==(const Node& b) const {
        return val == b.val;
    }
    bool operator<=(const Node& b) const {
        return val <= b.val;
    }
};
