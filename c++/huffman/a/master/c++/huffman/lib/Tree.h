//
// Created by user on 20.06.18.
//

#ifndef LIB_TREE_H
#define LIB_TREE_H

#include "BitSet.h"
#include <vector>

class Tree {
    class Node {
        unsigned char symbol;
        Node* sons[2];
        size_t _size;
    public:
        explicit Node(unsigned char s = 0, size_t si = 0, Node* ls = nullptr, Node* rs = nullptr);
        ~Node();
        Node* son(bool f);
        unsigned char getSymbol();
        size_t size();
    };

private:
    Node* root;
    Node* cur;
    std::vector <BitSet> codes;
    void createCodes(Tree::Node *v, BitSet& cd);

public:
    Tree();
    ~Tree();
    void deleteNode(Node* v);
    void buildTree(unsigned long long * mas);
    void move(bool f);
    bool isTerminal();
    void toRoot();
    unsigned char getCurSymbol();
    BitSet getCode(unsigned char symbol);
    bool isRoot();
};

#endif //LIB_TREE_H
