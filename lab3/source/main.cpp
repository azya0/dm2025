#include <iostream>
#include <fstream>
#include <exception>

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

        for (auto adjacentNode : node->getRibs()) {
            std::cout << adjacentNode.first->getName() << ' ';
        }

        std::cout << '\n';
    }
}

int main() {
    std::string filename = "graph.txt";
    std::shared_ptr<Graph> graph;

    try {
        graph = std::make_shared<Graph>(parseFile(filename));

        Builder builder;

        auto result = builder.buildPowerSeries(graph);
        
        for (int index = 0; index < result->size(); index++) {
            std::cout << (*result)[index] << ' ';
        }

        graph = builder.buildGraph(result);

        if (graph == nullptr) {
            std::cout << "it was not possible to construct a graph from a power series";
        } else {
            std::cout << '\n';
            printGraph(graph);
        }
    } catch (std::exception& error) {
        std::cout << error.what();
        return 1;
    }

    return 0;
}
