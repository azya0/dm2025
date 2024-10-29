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

void printWay(std::queue<std::shared_ptr<Node>> const & way) {
    auto current = way;
    
    while (true) {
        std::cout << current.front()->getName();
        current.pop();
        

        if (current.empty()) {
            return;
        }

        std::cout << " -> "; 
    }
}

int main() {
    std::string filename;

    std::cin >> filename;

    std::shared_ptr<Graph> graph;

    try {
        graph = std::make_shared<Graph>(parseFile(filename));

        std::string graphName;
        std::cin >> graphName;

        auto data = graph->Ways(graphName);

        auto nodes = *graph->Nodes();

        for (auto &[key, value] : nodes) {
            auto nodeData = data.find(value);

            if (nodeData == data.end()) {
                std::cout << "no way " << graphName << " -> " << key << '\n';
                continue;
            }

            std::cout << graphName << " -> " << key << " : " << nodeData->second->first << ' '; 
            printWay(nodeData->second->second);
            std::cout << '\n';
        }
    } catch (std::exception& error) {
        std::cout << error.what();
        return 1;
    }

    return 0;
}
