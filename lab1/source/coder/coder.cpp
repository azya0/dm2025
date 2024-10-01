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

int Coder::getLettersWithProb(std::string const & filename, bool showCode) {
    struct TwoWayArray {
        TwoWayArray* prev = nullptr;
        TwoWayArray* next = nullptr;
        float probability = 0;
        char letter;
    };

    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("missed file " + filename);
    }

    input.unsetf(std::ios_base::skipws);
    
    std::unordered_map<char, TwoWayArray*> connection;
    TwoWayArray *start = nullptr, *end = nullptr;
    unsigned long counter = 0;
    char letter;

    while (!input.eof()) {
        input >> letter;
        counter++;

        TwoWayArray* element;

        if (connection.find(letter) == connection.end()) {
            element = new TwoWayArray();
            connection[letter] = element;
            element->letter = letter;
            
            if (start == nullptr) {
                end = element;
            } else {
                element->next = start;
                start->prev = element;
            }

            start = element;
        }

        element = connection[letter];

        element->probability++;

        TwoWayArray *next = element->next;

        while ((next != nullptr) && (element->probability > next->probability)) {
            next = next->next;
        }

        if (next == element->next) {
            continue;
        }

        if (element->prev != nullptr)
            element->prev->next = element->next;

        if (element->next != nullptr)
            element->next->prev = element->prev;

        if (element == start) {
            start = start->next;
        }
        
        if (next == nullptr) {
            end->next = element;
            element->prev = end;
            element->next = nullptr;
            end = element;
        } else {
            next = next->prev;

            element->prev = next;
            element->next = next->next;
            next->next = element;
            element->next->prev = element;
        }
    }

    input.close();

    auto current = end;

    while (current != nullptr) {
        auto toDelete = current;

        letters.push_back({current->letter, current->probability / counter});

        current = current->prev;

        delete toDelete;
    }

    buildCodes(showCode);

    return counter;
}

void Coder::buildCodes(bool showCode) {
    std::queue<std::pair<std::string, std::pair<int, int>>> queue;
    queue.push({"", {0, letters.size() - 1}});

    while (!queue.empty()) {
        auto element = queue.front();
        int startIndex = element.second.first, endIndex = element.second.second;

        if (startIndex == endIndex) {
            std::string copy(element.first);
            std::reverse(copy.begin(), copy.end());
            char letter = letters[startIndex].first;

            if (showCode) {
                std::cout << letter << " -> " << copy << '\n';
            }

            letterToCode[letter] = copy;
        } else {
            int mediana = findMediana(startIndex, endIndex);
            queue.push({'0' + element.first, {startIndex, mediana}});
            queue.push({'1' + element.first, {mediana + 1, endIndex}});
        }

        queue.pop();
    }
}

void Coder::code(std::string const &filename, std::string const &newFilename, bool showCode) {
    int numberOfLetters = getLettersWithProb(filename, showCode);

    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("miss input file");
    }

    std::ofstream output(newFilename, std::ofstream::binary);

    if (!output.is_open()) {
        throw std::runtime_error("miss output file");
    }

    output << numberOfLetters << ' ' << letterToCode.size() << ' ';

    BinaryString bstring;
    for (auto &[letter, code] : letterToCode) {
        bstring.placeChar(letter);
        bstring.placeChar((uint8_t)code.size());
        for (auto letter : code) {
            bstring.placeBit(letter - '0');
        }
    }

    input.unsetf(std::ios_base::skipws);

    char letter;
    while (!input.eof()) {
        input >> letter;

        for (auto letter : letterToCode[letter]) {
            bool isPrintable = bstring.placeBit(letter - '0');

            if (isPrintable) {
                output << bstring.getString();
                bstring.clear();
            }
        }
    }

    input.close();

    bstring.end();
    output << bstring.getString();
    
    output.close();
}

void Coder::decode(std::string const &filename, std::string const &newFilename, bool showCode) {
    std::ifstream input(filename, std::ofstream::binary);

    if (!input.is_open()) {
        throw std::runtime_error("miss input file");
    }

    std::ofstream output(newFilename);

    if (!output.is_open()) {
        throw std::runtime_error("miss output file");
    }

    int numberOfLetters, numberOfCodes;
    input >> numberOfLetters;
    input >> numberOfCodes;

    input.unsetf(std::ios_base::skipws);

    BinaryReader reader;
    uint8_t buffer;
    input >> buffer;

    for (int _ = 0; _ < numberOfCodes; _++) {
        input >> buffer;
        reader.add(buffer);
        char letter = reader.next(8);

        input >> buffer;
        reader.add(buffer);
        uint8_t length = reader.next(8);

        std::string code;
        for (int _ = 0; _ < length; _++) {
            if (reader.empty()) {
                input >> buffer;
                reader.add(buffer);
            }
            
            code += '0' + reader.next(1);
        }
        
        if (showCode) {
            std::cout << code << " -> " << letter << '\n';
        }

        codeToLetter[code] = letter;
    }

    int counter = 0;
    std::string code;

    while (counter < numberOfLetters) {
        if (reader.empty()) {
            input >> buffer;
            reader.add(buffer);
        }

        code += '0' + reader.next(1);

        if (codeToLetter.find(code) != codeToLetter.end()) {
            output << codeToLetter[code];
            code.clear();
            counter++;
        }
    }

    input.close();
    output.close();
}
