#include "graph.h"

Node::Node(std::shared_ptr<std::vector<Rib>> nodes, std::string const & _name) : Node(name) {
    for (auto rib : (*nodes)) {
        (*ribs)[rib.first] = rib.second;
    }
}

Node::Node(std::string const &_name) {
    name = _name;
    ribs = std::make_shared<RibContainer>();
}

std::shared_ptr<Node::RibContainer> Node::Nodes() {
    return ribs;
}

void Node::addRib(std::shared_ptr<Node> rib, int weight) {
    (*ribs)[rib] = weight;
}

void Node::rmRib(std::shared_ptr<Node> rib) {
    ribs->erase(rib);
}


std::string const & Node::getName() {
    return name;
}

int Node::ribNumber() const {
    return (*ribs).size();
}

Graph::Graph(std::vector<GraphData> data) {
    std::unordered_map<
        std::shared_ptr<Node>,
        std::vector<GraphData::DataPair>
    > toAdd;
    
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

std::shared_ptr<Graph::NodesT> Graph::Nodes() {
    return std::make_shared<Graph::NodesT>(nodes);
}
