//
// Created by user on 20.06.18.
//

#ifndef LIB_BITSEQ_H
#define LIB_BITSEQ_H

#include <vector>

class BitSet {
    std::vector <unsigned long long> bits;
    size_t _size;

public:
    BitSet();
    ~BitSet() = default;
    size_t size();
    void add(bool x);
    void append(BitSet x);
    void pop();
    unsigned char* write(bool f);
    void clear();
};

#endif //LIB_BITSEQ_H
