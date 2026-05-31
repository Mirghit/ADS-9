// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <cstdint>
#include <vector>

class PMTree {
 public:
    struct Node {
        char val;
        std::vector<Node*> childs;
        explicit Node(char v) : val(v) {}
    };
    Node *root;
    int size;
    explicit PMTree(const std::vector<char>& chs);
    ~PMTree();

 private:
    Node* buildSubtree(const std::vector<char>& other);
    void deleteNode(Node *node);
};

std::vector<std::vector<char>> getAllPerms(const PMTree &tree);
std::vector<char> getPerm1(const PMTree &tree, int loc);
std::vector<char> getPerm2(const PMTree &tree, int loc);
uint64_t factorial(int n);

#endif  // INCLUDE_TREE_H_
