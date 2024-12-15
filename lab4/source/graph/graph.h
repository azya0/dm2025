#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>

class Node {
public:
    using Rib = std::pair<std::shared_ptr<Node>, int>;
    using RibContainer = std::unordered_map<std::shared_ptr<Node>, int>;

    Node(std::string const & name);
    Node(std::shared_ptr<std::vector<Rib>> nodes, std::string const & name);

    std::shared_ptr<RibContainer> Nodes();

    void addRib(std::shared_ptr<Node> rib, int weight);

    void rmRib(std::shared_ptr<Node> rib);

    std::string const & getName();

    int ribNumber() const;
private:
    std::shared_ptr<RibContainer> ribs;
    std::string name;
};

struct GraphData {
    using DataPair = std::pair<std::string, int>;

    std::string name;
    
    std::vector<DataPair> ribs;
};

class Graph {
public:
    using NodesT = std::unordered_map<std::string, std::shared_ptr<Node>>;
private:
    NodesT nodes;
public:
    Graph(std::vector<GraphData> data);

    std::shared_ptr<Node> find(std::string const & target);

    std::shared_ptr<NodesT> Nodes();
};
