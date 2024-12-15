#include <memory>
#include <vector>
#include <stack>

#include "../graph/graph.h"

class Builder {
public:
    using Loop = std::vector<std::shared_ptr<Node>>;

    static bool isEuler(std::shared_ptr<Graph> graph);

    static std::shared_ptr<Loop> eulerLoop(std::shared_ptr<Graph> graph);
};