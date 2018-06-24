//
// Created by user on 20.06.18.
//

#ifndef LIB_BITSEQ_H
#define LIB_BITSEQ_H

#include <vector>

class BitSeq {
    std::vector <unsigned long long> bits;
    size_t _size;

public:
    BitSeq();
    ~BitSeq() = default;
    size_t size();
    void add(bool x);
    void append(BitSeq x);
    void pop();
    unsigned char* write(bool f);
    void clear();
};

#endif //LIB_BITSEQ_H
