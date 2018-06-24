#include <iostream>

#include "gtest/gtest.h"
#include "../huffman.h"

TEST(correctness, empty) {
    std::stringstream in("");
    std::stringstream c;
    std::stringstream d;

    Huffman::compress(in, c);
    Huffman::decompress(c, d);

    EXPECT_EQ(in.str(), d.str());
}

TEST(correctness, one_symbol) {
    std::stringstream in("a");
    std::stringstream c;
    std::stringstream d;

    Huffman::compress(in, c);
    Huffman::decompress(c, d);

    EXPECT_EQ(in.str(), d.str());
}

TEST(correctness, all_char) {
    std::stringstream in;
    std::stringstream c;
    std::stringstream d;

    for (int i = -128; i <= 127; i++) {
        in << char(i);
    }

    Huffman::compress(in, c);
    Huffman::decompress(c, d);

    EXPECT_EQ(in.str(), d.str());
}

TEST(correctness, rand_big) {
    std::stringstream in;
    std::stringstream c;
    std::stringstream d;

    for (int i = 0; i < int(1e7); i++) {
        in << (char(rand() % 256));
    }

    Huffman::compress(in, c);
    Huffman::decompress(c, d);

    EXPECT_EQ(in.str(), d.str());
}

TEST(correctness, invalid_file) {
    std::stringstream c;
    std::stringstream d("");

    c << "abacabadaaba";

    EXPECT_EQ(false, Huffman::decompress(c, d));
}

TEST(correctness, null_string) {
    std::stringstream in;
    std::stringstream c;
    std::stringstream d;

    for (int i = 0; i < 100; i++) {
        in << char(0);
    }

    Huffman::compress(in, c);
    Huffman::decompress(c, d);

    EXPECT_EQ(in.str(), d.str());
}

TEST(correctness, equal_compressing) {
    std::stringstream in;
    std::stringstream c;
    std::stringstream d;

    for (int i = 0; i < 2000; i++) {
        in << char(rand() % 256);
    }

    Huffman::compress(in, c);
    Huffman::compress(in, d);
    EXPECT_EQ(c.str(), d.str());
}