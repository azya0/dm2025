#include <iostream>
#include "pqueue/pqueue.h"

bool chooseFunction(int first, int second) {
    return first < second;
}

int main() {
    std::vector<int> array = {35, 38, 29, 91, 61, 47, 50, 14, 75, 84};

    PQueue<int> queue(std::make_shared<std::function<bool(int, int)>>(chooseFunction));

    for (auto value : array) {
        queue.push(value);
    }

    std::vector<int> check;

    while (!queue.empty()) {
        check.push_back(queue.pop());
    }

    for (auto value : check) {
        std::cout << value << ' ';
    }

    return 0;
}
