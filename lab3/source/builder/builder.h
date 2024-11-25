#include <algorithm>

#include "../pqueue/pqueue.h"
#include "../graph/graph.h"

class Builder {
public:
    static std::shared_ptr<std::vector<int>> buildPowerSeries(std::shared_ptr<Graph> graph);

    using Pair = std::pair<int, int>;
    static std::shared_ptr<Graph> buildGraph(std::shared_ptr<std::vector<int>> powerSeries);
};
