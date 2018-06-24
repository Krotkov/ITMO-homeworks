#include <iostream>
#include <fstream>
#include <cstring>
#include "lib/Tree.h"
#include "lib/huffman.h"

void correctInput() {
    std::cout << "usage: ./huffman <-c | -d> input output" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        correctInput();
        return 0;
    }
    auto option = std::string(argv[1]);
    auto input = std::string(argv[2]);
    auto output = std::string(argv[3]);
    std::ifstream in(input, std::ifstream::binary);
    std::ofstream out(output, std::ofstream::binary);
    if (!in.is_open() || !out.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 0;
    }
    if (option == "-c") {
        Huffman::compress(in, out);
    } else if (option == "-d") {
        if (!Huffman::decompress(in, out)) {
            std::cout << "Invalid file\n";
        }
    } else {
        correctInput();
    }
    return 0;
}