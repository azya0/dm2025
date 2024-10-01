#include "bstring.h"

bool BinaryString::placeBit(uint8_t bit) {
    if (bit > 1)
        throw std::runtime_error("bit should be includet in [0, 1]");

    if (counter % 8 == 0) {
        string.push_back(bit);
        counter = 1;
        return false;
    }

    counter++;

    string.back() = (string.back() << 1) + bit;

    return counter == 8;
}

void BinaryString::placeChar(char letter) {
    std::string result;

    while (letter != 0) {
        result = (char)((letter % 2) + '0') + result;
        letter >>= 1;
    }

    while (result.size() != 8) {
        result = '0' + result;
    }

    placeCode(result);
}

void BinaryString::placeCode(std::string const &code) {
    for (auto letter : code) {
        placeBit(letter - '0');
    }
}

void BinaryString::end() {
    uint8_t more = (counter % 8 == 0) ? 8 : counter;

    while (counter != 8) {
        placeBit(0);
    }
}

std::string BinaryString::getString() {
    return string;
}

void BinaryString::clear() {
    string.clear();
    counter = 0;
}
