#pragma once

#include "../bstring/bstring.h"
#include "../breader/breader.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <limits>

class Coder {
private:
    std::vector<std::pair<char, float>> letters;
    std::unordered_map<std::string, char> codeToLetter;
    std::unordered_map<char, std::string> letterToCode;

    int findMediana(int startIndex, int endIndex);

    int getLettersWithProb(std::string const & filename, bool showCode);

    void buildCodes(bool showCode);
public:
    void code(std::string const &filename, std::string const &newFilename, bool showCode);

    void decode(std::string const &filename, std::string const &newFilename, bool showCode);
};
