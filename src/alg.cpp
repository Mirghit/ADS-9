// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdint>
#include <vector>
#include "tree.h"

uint64_t factorial(int n) {
    uint64_t res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

static void navigationg(PMTree::Node *node, int remaining,
                        uint64_t num, std::vector<char>& res) {
    if (remaining == 0) return;
    uint64_t block = factorial(remaining - 1);
    for (PMTree::Node *child : node->childs) {
        if (num <= block) {
            res.push_back(child->val);
            navigationg(child, remaining - 1, num, res);
            return;
        } else {
            num -= block;
        }
    }
}

PMTree::PMTree(const std::vector<char> &chs) {
    std::vector<char> sortedChs = chs;
    std::sort(sortedChs.begin(), sortedChs.end());
    size = static_cast<int>(sortedChs.size());
    root = new Node('\0');
    for (char c : sortedChs) {
        std::vector<char> other;
        other.push_back(c);
        for (char cc : sortedChs) {
            if (cc != c) other.push_back(cc);
        }
        root->childs.push_back(buildSubtree(other));
    }
}

PMTree::Node *PMTree::buildSubtree(const std::vector<char> &other) {
    if (other.empty()) return nullptr;
    Node *currNode = new Node(other[0]);
    if (other.size() == 1) return currNode;
    for (size_t i = 1; i < other.size(); ++i) {
        std::vector<char> next;
        next.push_back(other[i]);
        for (size_t j = 1; j < other.size(); ++j) {
            if (j != i) next.push_back(other[j]);
        }
        currNode->childs.push_back(buildSubtree(next));
    }
    return currNode;
}

void PMTree::deleteNode(Node *node) {
    if (!node) return;
    for (Node *child : node->childs) deleteNode(child);
    delete node;
}

PMTree::~PMTree() {
    deleteNode(root);
}

static void dSearch(PMTree::Node *node,
                    std::vector<char>& way,
                    std::vector<std::vector<char>>& result) {
    if (node->childs.empty()) {
        result.push_back(way);
        return;
    }
    for (PMTree::Node *child : node->childs) {
        way.push_back(child->val);
        dSearch(child, way, result);
        way.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree &tree) {
    std::vector<std::vector<char>> res;
    if (!tree.root) return res;
    std::vector<char> way;
    for (PMTree::Node *child : tree.root->childs) {
        way.push_back(child->val);
        dSearch(child, way, res);
        way.pop_back();
    }
    return res;
}

std::vector<char> getPerm1(const PMTree &tree, int loc) {
    auto all = getAllPerms(tree);
    if (loc >= 1 && static_cast<size_t>(loc) <= all.size())
        return all[loc - 1];
    return {};
}

std::vector<char> getPerm2(const PMTree &tree, int loc) {
    int n = tree.size;
    uint64_t whole = factorial(n);
    if (loc < 1 || static_cast<uint64_t>(loc) > whole) return {};
    std::vector<char> result;
    result.reserve(n);
    navigationg(tree.root, n, static_cast<uint64_t>(loc), result);
    return result;
}
