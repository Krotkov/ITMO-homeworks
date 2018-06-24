//
// Created by user on 20.06.18.
//
#include <iostream>
#include "BitSeq.h"

size_t BitSeq::size() {
    return _size;
}

BitSeq::BitSeq() {
    _size = 0;
}

void BitSeq::add(bool x) {
    if ((_size & 63) == 0) bits.push_back(0);
    bits.back() += ((unsigned long long)(x) << (63 - (_size & 63)));
    _size++;
}

void BitSeq::append(BitSeq x) {
    size_t shift = 0;
    shift = (_size & 63);
    if (shift == 0) {
        for (unsigned long long bit : x.bits) {
            bits.push_back(bit);
        }
    } else {
        for (size_t i = 0; i < x.bits.size(); i++) {
            bits.back() += (x.bits[i] >> shift);
            x.bits[i] <<= (64 - shift);
            if (x.size() > i*64 + 64 - shift) bits.push_back(x.bits[i]);
        }
    }
    _size += x.size();
}

void BitSeq::pop() {
    if (_size == 0) return;
    bits.back() &= ((unsigned long long)(-1) - (1ull << (63 - (_size & 63))));
    _size--;
    if ((_size >> 6) + ((_size & 63) != 0) < (bits.size())) bits.pop_back();
}

unsigned char *BitSeq::write(bool f) {
    size_t new_size = 0;
    unsigned long long ost = 0;
    if (_size == 0 || bits.empty()) return nullptr;
    if (f && (_size & 63) != 0) {
        ost = bits.back();
        new_size = (_size & 63);
        _size -= new_size;
        bits.pop_back();
    }
    size_t len = _size / 8 + ((_size & 3) != 0);
    auto ans = new unsigned char[len];
    for (size_t i = 0; i < bits.size(); i++) {
        for (int j = 7; j >= 0; j--) {
            if (i * 8 + (7-j) < len) ans[i*8 + 7 - j] = (unsigned char)(bits[i] >> (j*8));
            else break;
        }
    }
    clear();
    if (new_size != 0) {
        bits.push_back(ost);
        _size = new_size;
    }
    return ans;
}

void BitSeq::clear() {
    _size = 0;
    bits.clear();
}

