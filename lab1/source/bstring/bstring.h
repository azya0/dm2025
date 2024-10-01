#pragma once

#include <iostream>
#include <string>

class BinaryString {
    std::string string;
    uint8_t counter = 0;
public:
    bool placeBit(uint8_t const bit);
    void placeChar(char letter);
    void placeCode(std::string const & code);
    void end();

    std::string getString();
    void clear();
};