#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>

#include "../bin-tree/bin-tree.h"


class Coder {
private:
    std::vector<std::pair<char, float>> letters;
    std::unordered_map<std::string, char> codesToLetters;
    std::unordered_map<char, std::string> lettersToCodes;

    int findMediana(int startIndex, int endIndex);

    void buildCodeTree();
public:
    Coder(std::string const & filename);

    void code(std::string const & filename);

    void decode(std::string const & filename);

    void print();
};
