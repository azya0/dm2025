#include <iostream>
#include <fstream>
#include <exception>

#include "graph/graph.h"

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

int main() {
    std::string filename;

    std::cin >> filename;

    std::shared_ptr<Graph> graph;

    try {
        graph = std::make_shared<Graph>(parseFile(filename));
        std::cout << graph->Way("A", "C").second;
    } catch (std::exception& error) {
        std::cout << error.what();
        return 1;
    }

    return 0;
}
