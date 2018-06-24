//
// Created by user on 20.06.18.
//
#include <set>
#include <iostream>
#include "Tree.h"


Tree::Node::Node(unsigned char s, size_t si, Tree::Node *ls, Tree::Node *rs) {
    _size = si;
    symbol = s;
    sons[0] = ls;
    sons[1] = rs;
}

Tree::Node::~Node() {
    sons[0] = nullptr;
    sons[1] = nullptr;
}

Tree::Node *Tree::Node::son(bool f) {
    return sons[int(f)];
}

unsigned char Tree::Node::getSymbol() {
    return symbol;
}

size_t Tree::Node::size() {
    return _size;
}


Tree::Tree() {
    root = nullptr;
    cur = nullptr;
    codes.resize(256);
}

void Tree::move(bool f) {
    cur = cur->son(f);
}

bool Tree::isTerminal() {
    return (cur->son(false) == nullptr && cur->son(true) == nullptr);
}

void Tree::toRoot() {
    cur = root;
}

unsigned char Tree::getCurSymbol() {
    return  cur->getSymbol();
}

Tree::~Tree() {
    deleteNode(root);
}

void Tree::buildTree(unsigned long long *mas) {
    auto cmp = [](Node *a, Node *b) { return a->size() < b->size(); };
    std::multiset<Node*, decltype(cmp)> se(cmp);
    for (size_t i = 0; i < 256; i++) {
        if (mas[i] != 0) se.insert(new Node((unsigned char) i, mas[i], nullptr, nullptr));
    }
    while (se.size() != 1) {
        Node* first = *se.begin();
        se.erase(se.begin());
        Node* second = *se.begin();
        se.erase(se.begin());
        se.insert(new Node(0, first->size() + second->size(), first, second));
    }
    root = *se.begin();
    cur = root;
    BitSeq a;
    createCodes(root, a);
}

void Tree::createCodes(Tree::Node *v, BitSeq &cd) {
    if (v->son(false) == nullptr && v->son(true) == nullptr) {
        if (cd.size() == 0) cd.add(false);
        unsigned char c = v->getSymbol();
        codes[c] = cd;
        return;
    }
    cd.add(false);
    createCodes(v->son(false), cd);
    cd.pop();
    cd.add(true);
    createCodes(v->son(true), cd);
    cd.pop();
}

BitSeq Tree::getCode(unsigned char symbol) {
    return codes[symbol];
}

void Tree::deleteNode(Tree::Node *v) {
    if (v == nullptr) return;
    deleteNode(v->son(false));
    deleteNode(v->son(true));
    delete v;
}

bool Tree::isRoot() {
    return cur == root;
}
