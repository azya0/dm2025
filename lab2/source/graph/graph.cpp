#include "graph.h"

Node::Node(std::shared_ptr<std::vector<Rib>> nodes, std::string const & _name) : Node(name) {
    ribs = std::move(*nodes);
}

Node::Node(std::string const &_name) {
    name = _name;
}

std::shared_ptr<std::vector<Node::Rib>> Node::Nodes()
{
    return std::make_shared<std::vector<Rib>>(std::move(ribs));
}

void Node::addRib(std::shared_ptr<Node> rib, int weight) {
    ribs.push_back({rib, weight});
}

std::vector<Node::Rib> Node::getRibs() {
    return ribs;
}

std::string const & Node::getName() {
    return name;
}

Graph::Graph(std::vector<GraphData> data) {
    std::unordered_map<std::shared_ptr<Node>, std::vector<GraphData::DataPair>> toAdd;
    
    for (auto graph : data) {
        auto currentNode = std::make_shared<Node>(graph.name);
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

std::pair<int, std::queue<std::shared_ptr<Node>>> Graph::Way(std::string const & from, std::string const & to) {
    auto start = find(from);
    auto target = find(to);

    using Way = std::queue<std::shared_ptr<Node>>;
    using Pair = std::pair<int, Way>;

    // OWL вмместо стека для удобной
    // сортировки для нахождения
    // минимального элемента
    // для оптимизации жадного
    // алгоритма
    typedef struct OWL {
        std::shared_ptr<OWL> next;
        std::shared_ptr<Pair> value;
    } OneWayList;
    
    std::unordered_map<
        std::shared_ptr<Node>,
        std::shared_ptr<Pair>
    > ways;

    auto startPair = std::make_shared<Pair>(0, Way({start}));
    ways[start] = startPair;

    auto stack = std::make_shared<OneWayList>(nullptr, nullptr);
    stack->next = std::make_shared<OneWayList>(nullptr, startPair);

    while (stack->next != nullptr) {
        auto current = stack->next->value;
        stack->next = stack->next->next;

        for (auto &[node, weight] : current->second.back()->getRibs()) {
            auto way = ways.find(node);
            int weightToNode = current->first + weight;

            if (way != ways.end() && way->second->first <= weightToNode) {
                continue;
            }

            auto copyPair = std::make_shared<Pair>(weightToNode, current->second);
            copyPair->second.push(node);

            ways[node] = copyPair;

            auto currentStack = stack;

            while (currentStack->next != nullptr && currentStack->next->value->first < weightToNode) {
                currentStack = currentStack->next;
            }
            
            currentStack->next = std::make_shared<OneWayList>(currentStack->next, copyPair);
        }
    }

    auto result = ways.find(target);

    if (result == ways.end()) {
        throw std::runtime_error("no ways found");
    }

    return (*result->second);
}
