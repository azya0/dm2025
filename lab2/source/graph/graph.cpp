#include "graph.h"

Node::Node(std::shared_ptr<std::vector<Rib>> nodes) {
    ribs = std::move(*nodes);
}

std::shared_ptr<std::vector<Node::Rib>> Node::Nodes() {
    return std::make_shared<std::vector<Rib>>(std::move(ribs));
}

void Node::addRib(std::shared_ptr<Node> rib, int weight) {
    ribs.push_back({rib, weight});
}

std::vector<Node::Rib> Node::getRibs() {
    return ribs;
}

Graph::Graph(std::vector<GraphData> data) {
    std::unordered_map<std::shared_ptr<Node>, std::vector<GraphData::DataPair>> toAdd;
    
    for (auto graph : data) {
        auto currentNode = std::make_shared<Node>();
        nodes[graph.name] = currentNode;

        for (auto rib : graph.ribs) {
            auto anotherNode = nodes.find(rib.first);
            if (anotherNode != nodes.end()) {
                currentNode->addRib(anotherNode->second, rib.second);
                continue;
            }

            toAdd[currentNode].push_back({rib.first, rib.second});
        }
    }

    for (auto &[key, valueList] : toAdd) {
        for (auto value : valueList) {
            key->addRib(nodes[value.first], value.second);
        }
    }
}

std::shared_ptr<Node> Graph::find(std::string const & target) {
    auto data = nodes.find(target);

    if (data == nodes.end()) {
        throw std::runtime_error("no " + target + " node found");
    }

    return data->second;
}

std::pair<std::shared_ptr<Graph::TwoWayList>, int> Graph::Way(std::string const & from, std::string const & to) {
    auto start = find(from);
    auto target = find(to);

    auto copy = [](TwoWayList value) {
        auto result = TwoWayList{
            value.to,
            value.weight,
            value.next,
            value.prev,
            value.start
        };

        return result;
    };

    // Буду использовать вместо стека
    // Для автоматической сортировки

    typedef struct OWL {
        std::shared_ptr<OWL> next;
        std::shared_ptr<TwoWayList> value;
    } OneWayList;
    
    std::unordered_map<
        std::shared_ptr<Node>,
        std::pair<int, std::shared_ptr<TwoWayList>>
    > ways;

    auto startWay = std::make_shared<TwoWayList>(start, 0, nullptr, nullptr, nullptr);
    ways[start] = {0, startWay};

    auto stack = std::make_shared<OneWayList>(nullptr, nullptr);
    stack->next = std::make_shared<OneWayList>(nullptr, startWay);

    while (stack->next != nullptr) {
        auto current = stack->next->value;
        stack->next = stack->next->next;

        for (auto &[node, weight] : current->to->getRibs()) {
            auto way = ways.find(node);
            int weightToNode = current->weight + weight;

            if (way != ways.end() && way->second.first <= weightToNode) {
                continue;
            }

            auto copyWay = std::make_shared<TwoWayList>(copy(*current));
            auto currentWay = std::make_shared<TwoWayList>(
                node,
                weightToNode,
                nullptr,
                copyWay,
                copyWay->start
            );
            copyWay->next = currentWay;

            ways[node] = {weightToNode, currentWay};

            auto currentStack = stack;

            while (currentStack->next != nullptr && currentStack->next->value->weight < weightToNode) {
                currentStack = currentStack->next;
            }
            
            currentStack->next = std::make_shared<OneWayList>(currentStack->next, currentWay);
        }
    }

    auto result = ways.find(target);

    if (result == ways.end()) {
        throw std::runtime_error("no ways found");
    }

    return {result->second.second->start, result->second.first};
}
