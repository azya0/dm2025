#include "breader.h"

void BinaryReader::add(uint8_t chunc) {
    if (empty()) {
        counter = 8;
    }
    
    data.push_back(chunc);
}

uint8_t BinaryReader::next(uint8_t chuncSize) {
    if (chuncSize > 8) {
        throw std::runtime_error("wrong chunc size");
    }

    if (!check(chuncSize)) {
        throw std::runtime_error("not enough data");
    }

    uint8_t result = 0;

    for (uint8_t index = 0; index < chuncSize; index++) {
        uint8_t bit = (data[0] >> 7) & 1;
        data[0] <<= 1;

        result = (result << 1) + bit;

        if (--counter == 0) {
            data = data.substr(1);

            if (data.size() != 0) {
                counter = 8;
            }
        }
    }

    return result;
}

int BinaryReader::size() {
    return counter + 8 * (data.size() - 1);
}

bool BinaryReader::empty() {
    return counter == 0;
}

bool BinaryReader::check(uint8_t chuncSize) {
    return chuncSize <= size();
}
