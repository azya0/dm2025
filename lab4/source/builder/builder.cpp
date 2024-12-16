#include "builder.h"

#include <iostream>

bool Builder::isEuler(std::shared_ptr<Graph> graph) {
    auto nodes = *(graph->Nodes());

    for (const auto& [_, value] : nodes) {
        int number = value->ribNumber();

        if ((number == 0) || (number % 2 != 0)) {
            return false;
        }
    }

    return true;
}

std::shared_ptr<Builder::Loop> Builder::eulerLoop(std::shared_ptr<Graph> graph) {
    if (!isEuler(graph)) {
        return nullptr;
    }
    
    auto result = std::make_shared<Builder::Loop>();
    std::stack<std::shared_ptr<Node>> nodeStack;
    nodeStack.push(graph->Nodes()->begin()->second);

    std::shared_ptr<Node> current, another;

    while (!nodeStack.empty()) {
        current = nodeStack.top();

        auto nodes = current->Nodes();

        if (nodes->empty()) {
            nodeStack.pop();
            result->push_back(current);
        } else {
            another = nodes->begin()->first;
            nodeStack.push(another);

            current->rmRib(another);
            another->rmRib(current);
        }
    }

    if (result->size() - 1 != graph->Nodes()->size()) {
        return nullptr;
    }

    return result;
}
