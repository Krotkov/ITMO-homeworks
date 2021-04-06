//
// Created by user on 20.06.18.
//

#ifndef LIB_HUFFMAN_H
#define LIB_HUFFMAN_H

#include <fstream>
#include "Tree.h"

class Huffman {
    static const size_t READ_BLOCK_SIZE = 1000;
    static const size_t WRITE_BLOCK_SIZE = 1000;
public:
    static void compress(std::istream &in, std::ostream &out);
    static bool decompress(std::istream &in, std::ostream &out);
};

#endif //LIB_HUFFMAN_H
