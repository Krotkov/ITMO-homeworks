//
// Created by user on 20.06.18.
//

#include <iosfwd>
#include <cstring>
#include <iostream>
#include "huffman.h"

void Huffman::compress(std::istream &in, std::ostream &out) {
    in.seekg(0, in.end);
    auto len = (size_t) in.tellg();
    if (in.peek() == EOF) return;
    in.seekg(std::istream::beg);
    unsigned long long num[256];
    std::fill(num, num + 256, 0);
    unsigned char notEmptySymbols = 0;
    unsigned char c[READ_BLOCK_SIZE + 1];
    size_t copy_len = len;
    while (copy_len != 0) {
        size_t loop = copy_len < READ_BLOCK_SIZE ? copy_len : READ_BLOCK_SIZE;
        in.read((char *) (&c), loop);
        copy_len -= loop;
        for (size_t i = 0; i < loop; i++) {
            num[c[i]]++;
        }
    }
    for (unsigned long long i : num) {
        if (i != 0) notEmptySymbols++;
    }
    out.put(notEmptySymbols);
    for (size_t i = 0; i < 256; i++) {
        if (num[i] != 0) {
            out.put((unsigned char) (i));
            for (int j = 7; j >= 0; j--) {
                out.put((unsigned char) (num[i] >> (j * 8)));
            }
        }
    }
    Tree huffmanTree;
    huffmanTree.buildTree(num);
    in.seekg(std::istream::beg);
    unsigned long long numOfBits = 0;
    for (size_t i = 0; i < 256; i++) {
        numOfBits += num[i] * huffmanTree.getCode((unsigned char) i).size();
    }
    for (int i = 7; i >= 0; i--) {
        out.put((unsigned char) (numOfBits >> (i * 8)));
    }
    BitSeq ans;
    copy_len = len;
    while (copy_len != 0) {
        size_t loop = copy_len < READ_BLOCK_SIZE ? copy_len : READ_BLOCK_SIZE;
        copy_len -= loop;
        in.read((char*) c, loop);
        for (size_t i = 0; i < loop; i++) {
            ans.append(huffmanTree.getCode(c[i]));
            if (ans.size() >= WRITE_BLOCK_SIZE * 8) {
                size_t wsize = ans.size() / 64 * 8;
                unsigned char *w;
                w = ans.write(true);
                out.write((char *) w, wsize);
                delete[] w;
            }
        }
    }
    unsigned char *w;
    if (ans.size() != 0) {
        size_t lenn = ans.size() / 8 + (ans.size() % 8 != 0);
        w = ans.write(false);
        out.write((char *) w, lenn);
        delete[] w;
    }
}

bool Huffman::decompress(std::istream &in, std::ostream &out) {
    in.seekg(0, in.end);
    auto fileSize = (unsigned long long) in.tellg();
    in.seekg(std::istream::beg);
    unsigned char notEmptySymbol;
    unsigned long long num[256];
    std::fill(num, num + 256, 0);
    if (in.peek() == EOF) return true;
    in.read((char *) &notEmptySymbol, 1);
    int notEmptySymbols = notEmptySymbol;
    if (notEmptySymbol == 0) notEmptySymbols = 256;
    for (unsigned short i = 0; i < notEmptySymbols; i++) {
        unsigned char symbol;
        if (in.peek() == EOF) return false;
        in.read((char *) &symbol, 1);
        for (size_t j = 0; j < 8; j++) {
            unsigned char c;
            if (in.peek() == EOF) return false;
            in.read((char *) &c, 1);
            num[symbol] = (num[symbol] << 8) + c;
        }
        if (num[symbol] == 0) return false;
    }
    Tree huffman_tree;
    huffman_tree.buildTree(num);
    size_t len = 0;
    unsigned char l[8];
    in.read((char *) l, 8);
    for (unsigned char i : l) {
        len = (len << 8) + i;
    }
    if (fileSize - len / 8 - (len % 8 != 0) != in.tellg()) return false;
    if (notEmptySymbols == 1) {
        for (int i = 0; i < len; i++) {
            out.put(huffman_tree.getCurSymbol());
        }
        return true;
    }
    char w[WRITE_BLOCK_SIZE];
    char r[READ_BLOCK_SIZE];
    short pos = 0;
    size_t copy_len = len / 8 + (len % 8 != 0);
    while (copy_len != 0) {
        size_t loop = copy_len < READ_BLOCK_SIZE ? copy_len : READ_BLOCK_SIZE;
        copy_len -= loop;
        in.read(r, READ_BLOCK_SIZE);
        for (size_t i = 0; i < loop; i++) {
            for (size_t j = 0; j < 8; j++) {
                if (i * 8 + j >= len) break;
                auto flag = bool(1 & (r[i] >> (7 - j)));
                huffman_tree.move(flag);
                if (huffman_tree.isTerminal()) {
                    w[pos] = huffman_tree.getCurSymbol();
                    pos++;
                    if (pos == WRITE_BLOCK_SIZE) {
                        out.write(w, WRITE_BLOCK_SIZE);
                        pos = 0;
                    }
                    huffman_tree.toRoot();
                }
            }
        }
        len -= loop * 8;
    }
    if (!huffman_tree.isRoot()) return false;
    if (pos != 0) {
        out.write(w, pos);
    }
    return true;
}
