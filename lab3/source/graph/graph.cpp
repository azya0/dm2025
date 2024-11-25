#include "graph.h"

Node::Node(std::shared_ptr<std::vector<Rib>> nodes, std::string const & _name) : Node(name) {
    ribs = std::move(*nodes);
}

Node::Node(std::string const &_name) {
    name = _name;
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

std::string const & Node::getName() {
    return name;
}

int Node::ribNumber() const {
    return ribs.size();
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

std::shared_ptr<Graph::NodesT const> Graph::Nodes() {
    return std::make_shared<Graph::NodesT const>(nodes);
}
