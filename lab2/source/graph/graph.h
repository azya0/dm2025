#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <queue>

class Node {
public:
    using Rib = std::pair<std::shared_ptr<Node>, int>;

    Node(std::string const & name);
    Node(std::shared_ptr<std::vector<Rib>> nodes, std::string const & name);

    std::shared_ptr<std::vector<Rib>> Nodes();

    void addRib(std::shared_ptr<Node> rib, int weight);

    std::vector<Node::Rib> getRibs();

    std::string const & getName();
private:
    std::vector<Node::Rib> ribs;
    std::string name;
};

struct GraphData {
    using DataPair = std::pair<std::string, int>;

    std::string name;
    
    std::vector<DataPair> ribs;
};

class Graph {
public:
    using WayT = std::queue<std::shared_ptr<Node>>;
    using Pair = std::pair<int, WayT>;
    using NodesT = std::unordered_map<std::string, std::shared_ptr<Node>>;
private:
    NodesT nodes;
public:
    Graph(std::vector<GraphData> data);

    std::shared_ptr<Node> find(std::string const & target);

    std::shared_ptr<NodesT const> Nodes();

    std::unordered_map<
        std::shared_ptr<Node>,
        std::shared_ptr<Pair>
    > Ways(std::string const & from);

    Pair Way(std::string const & from, std::string const & to);
};
