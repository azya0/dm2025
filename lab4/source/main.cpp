#include <iostream>
#include <fstream>

#include "graph/graph.h"
#include "builder/builder.h"

std::vector<GraphData> parseFile(std::string const & filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("miss file \"" + filename + "\"");
    }

    std::vector<GraphData> result;

    while (!file.eof()) {
        std::string graphName;
        file >> graphName;

        int ribsNumber = 0;

        file >> ribsNumber;
        std::vector<GraphData::DataPair> ribs;

        for (int _ = 0; _ < ribsNumber; _++) {
            std::string ribName;
            int weight = 0;

            file >> ribName;
            file >> weight;
            
            ribs.push_back({ribName, weight});
        }

        result.push_back(GraphData{graphName, ribs});
    }

    file.close();

    return result;
}

void printGraph(std::shared_ptr<Graph> graph) {
    auto nodes = graph->Nodes();

    for (auto &[name, node] : *nodes) {
        std::cout << name << " -> ";

        for (auto adjacentNode : (*node->Nodes())) {
            std::cout << adjacentNode.first->getName() << ' ';
        }

        std::cout << '\n';
    }
}

void printLoop(std::shared_ptr<Builder::Loop> loop) {
    std::cout << "Loop:\n";

    if (loop->size() == 0) {
        std::cout << "Empty?...";
        return;
    }

    std::cout << (*loop)[0]->getName();

    for (int index = 1; index < loop->size(); index++) {
        std::cout << " -> " << (*loop)[index]->getName();
    }

    std::cout << '\n';
}

int main() {
    std::string filename = "graph.txt";
    std::shared_ptr<Graph> graph;

    try {
        graph = std::make_shared<Graph>(parseFile(filename));

        printGraph(graph);

        auto data = Builder::eulerLoop(graph);

        if (data == nullptr) {
            std::cout << "No euler loop";
        } else {
            printLoop(data);
        }
    } catch (std::exception& error) {
        std::cout << "Unexpected error: " << error.what();
        return 1;
    }

    return 0;
}
