#include "builder.h"

std::shared_ptr<std::vector<int>> Builder::buildPowerSeries(std::shared_ptr<Graph> graph) {
    auto nodes = graph->Nodes();
    auto result = std::make_shared<std::vector<int>>();

    for (auto &[_, value] : *nodes) {
        result->push_back((*value).ribNumber());
    }

    std::sort(result->begin(), result->end());
    
    return result;
}

bool anotherCompareFunction(Builder::Pair first, Builder::Pair second) {
    return first.first > second.first;
}

std::string nameFromInt(int value) {
    std::string result = "";
    
    for (int index = 0; index < value / 26; index++) {
        result += 'A';
    }

    result += ('A' + (value % 26));

    return result;
}

std::shared_ptr<Graph> Builder::buildGraph(std::shared_ptr<std::vector<int>> powerSeries) {
    std::vector<Pair> data(powerSeries->size());
    PQueue<Pair> pqueue(std::make_shared<std::function<bool(Pair, Pair)>>(anotherCompareFunction));
    
    std::vector<GraphData> graphData(powerSeries->size());

    for (int index = 0; index < graphData.size(); index++) {
        graphData[index].name = nameFromInt(index);
        data[index] = std::make_pair((*powerSeries)[index], index);
    }

    pqueue.fromVector(data);

    while (!pqueue.empty()) {
        Pair current = pqueue.pop();

        if (current.first > pqueue.size()) {
            return nullptr;
        }

        std::vector<Pair> container;
        
        for (int index = 0; index < current.first; index++) {
            Pair currentAdjacent = pqueue.pop();

            if (currentAdjacent.first == 0) {
                return nullptr;
            }

            graphData[currentAdjacent.second].ribs.push_back({graphData[current.second].name, 1});
            graphData[current.second].ribs.push_back({graphData[currentAdjacent.second].name, 1});

            if (currentAdjacent.first > 1) {
                currentAdjacent.first--;
                container.push_back(currentAdjacent);
            }
        }

        for (auto value : container) {
            pqueue.push(value);
        }
    }

    return std::make_shared<Graph>(graphData);
}
