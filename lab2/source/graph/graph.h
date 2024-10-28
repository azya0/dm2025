#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>

class Node {
public:
    using Rib = std::pair<std::shared_ptr<Node>, int>;

    Node() {};
    Node(std::shared_ptr<std::vector<Rib>> nodes);

    std::shared_ptr<std::vector<Rib>> Nodes();

    void addRib(std::shared_ptr<Node> rib, int weight);

    std::vector<Node::Rib> getRibs();
private:
    std::vector<Node::Rib> ribs;
};

struct GraphData {
    using DataPair = std::pair<std::string, int>;

    std::string name;
    
    std::vector<DataPair> ribs;
};

class Graph {
private:
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes;
public:
    Graph(std::vector<GraphData> data);

    std::shared_ptr<Node> find(std::string const & target);

    // Двусвязный список для того, чтобы
    // При итерациях в Way(...)
    // не удалялся предыдущий элемент

    typedef struct TWL {
        std::shared_ptr<Node> to;
        int weight;

        std::shared_ptr<TWL> next;
        std::shared_ptr<TWL> prev;
        std::shared_ptr<TWL> start;
    } TwoWayList;

    std::pair<std::shared_ptr<TwoWayList>, int> Way(std::string const & from, std::string const & to);
};
