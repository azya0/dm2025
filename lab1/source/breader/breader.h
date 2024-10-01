#pragma once

#include <iostream>

class BinaryReader {
private:
    std::string data;
    uint8_t counter = 0;
public:
    void add(uint8_t chunc);

    uint8_t next(uint8_t chuncSize);

    int size();

    bool empty();

    bool check(uint8_t chuncSize);
};
