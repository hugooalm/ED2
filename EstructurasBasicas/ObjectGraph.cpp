#include <iostream>
#include <memory>
#include <unordered_map>

struct City {
    std::string name{};
    int population{};
    float surface{};

    using ID = std::string;
    ID getID() {return name;}
    auto operator<=>(const City& rhs) const = default;
};

template<>
struct std::hash<City> {
    std::size_t operator()(const City& city) const {
        return (std::hash<std::string>()(city.name));
    }
};

template<typename T, typename W>
class ObjectGraph {
public:

/*
 * addNode
 * setEdge
 * getEdges
 * getEdge 2 nodos dados
 * removeNode
 * getNode (objectGraph)
 */

    void addNode(T node){
        nodes[node.getID()] = {};
        reverse[node.getID()] = node;
    }

    void setEdge(T sourceNode, T targetNode, W weight) {
        nodes[sourceNode.getID()][targetNode.getID()] = weight;
        nodes[targetNode.getID()][sourceNode.getID()] = weight; // No dirigido
    }
    void setEdge(typename T::ID sourceNode, typename T::ID targetNode, W weight) {
        nodes[sourceNode][targetNode] = weight;
        nodes[targetNode][sourceNode] = weight; // No dirigido
    }

    const std::unordered_map<typename T::ID, W>& getEdges(T node) const {
        return nodes[node.getID()];
    }
    const std::unordered_map<typename T::ID, W>& getEdges(typename T::ID node) const {
        return nodes[node];
    }

    W getEdge(T sourceNode, T targetNode) {
        return nodes[sourceNode.getID()][targetNode.getID()];
    }
    W getEdge(typename T::ID sourceNode, typename T::ID targetNode) {
        return nodes[sourceNode.getID()][targetNode.getID()];
    }

    void removeNode(T node) {
        auto &aux = nodes[node.getID()];
        for (const auto &[target, weight]: aux) {
            nodes[target].erase(node.getID());
        }
        nodes.erase(node.getID());
        reverse.erase(node.getID());
    }
    void removeNode(typename T::ID node) {
        auto &aux = nodes[node];
        for (const auto &[target, weight]: aux) {
            nodes[target].erase(node);
        }
        nodes.erase(node);
        reverse.erase(node);
    }

    T& getNode(typename T::ID nodeID){return reverse[nodeID];}

    auto begin() {return nodes.begin();}
    auto end() {return nodes.end();}

private:
    std::unordered_map<typename T::ID, std::unordered_map<typename T::ID, W>> nodes;
    std::unordered_map<typename T::ID, T> reverse;
};

