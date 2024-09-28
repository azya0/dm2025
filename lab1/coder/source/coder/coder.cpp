#include "coder.h"

int Coder::findMediana(int startIndex, int endIndex) {
    float firstPartSum = letters[startIndex].second, secondPartSum = 0;

    for (int index = startIndex + 1; index <= endIndex; index++) {
        secondPartSum += letters[index].second;
    }

    int mediana = startIndex;
    float control = 0.f;

    do {
        control = std::abs(secondPartSum - firstPartSum);

        mediana += 1;

        float difference = letters[mediana].second;
        firstPartSum += difference;
        secondPartSum -= difference;
    } while (std::abs(secondPartSum - firstPartSum) < control);

    return mediana - 1;
}

void Coder::buildCodeTree() {
    std::queue<std::pair<std::string, std::pair<int, int>>> queue;
    queue.push({"", {0, letters.size() - 1}});

    while (!queue.empty()) {
        auto element = queue.front();
        int startIndex = element.second.first, endIndex = element.second.second;

        if (startIndex == endIndex) {
            std::string copy(element.first);
            std::reverse(copy.begin(), copy.end());

            codesToLetters[copy] = letters[startIndex].first;
            lettersToCodes[letters[startIndex].first] = copy;
        } else {
            int mediana = findMediana(startIndex, endIndex);
            queue.push({'0' + element.first, {startIndex, mediana}});
            queue.push({'1' + element.first, {mediana + 1, endIndex}});
        }

        queue.pop();
    }
    
}

Coder::Coder(std::string const &filename) {
    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("missed file " + filename);
    }
    
    int letterCode;
    float value;

    while (!input.eof()) {
        input >> letterCode;
        input >> value;

        letters.push_back({(char)(letterCode), value});
    }

    input.close();

    buildCodeTree();
}

void Coder::code(std::string const &filename, bool showCode) {
    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("missed file " + filename);
    }

    input.unsetf(std::ios_base::skipws);

    std::ofstream output(filename + "-coded");

    char letter;

    while (!input.eof()) {
        input >> letter;

        std::string code = lettersToCodes[letter];

        if (showCode) {
            std::cout << "Char: \"" << letter << '"' << " coded as: \"" << code << "\"\n";
        }

        output << code;
    }

    input.close();
    output.close();
}

void Coder::code(std::string const &filename) {
    code(filename, false);
}

void Coder::decode(std::string const &filename, bool showCode) {
    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("missed file " + filename);
    }

    std::ofstream output(filename + "-decoded");

    std::string code;
    char letter;

    while (!input.eof()) {
        input >> letter;

        code += letter;

        if (codesToLetters.find(code) != codesToLetters.end()) {
            char letter = codesToLetters[code];

            if (showCode) {
                std::cout << "Code: \"" << code << '"' << " decoded as: \"" << letter << "\"\n";
            }

            output << letter;
            code.clear();
        }
    }

    input.close();
    output.close();
}

void Coder::decode(std::string const &filename) {
    decode(filename, false);
}

void Coder::print() {
    for (auto element : lettersToCodes) {
        std::cout << element.first << " -> " << element.second << '\n';
    }
}
