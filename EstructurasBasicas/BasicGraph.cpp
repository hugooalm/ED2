#include <iostream>
#include <memory>
#include <unordered_map>

template<typename T, typename W>
class BasicGraph {
public:
    void addNode(T node) {
        nodes[node] = {};
    }

    void setEdge(T sourceNode, T targetNode, W weight) {
        nodes[sourceNode][targetNode] = weight;
        nodes[targetNode][sourceNode] = weight; // No direccionado
    }

    const std::unordered_map<T, W>& getEdges(T node) const {
        return nodes[node];
    }

    // No puede ser const porque puede crear la arista vacia si no existe
    W getEdge(T sourceNode, T targetNode) {
        return nodes[sourceNode][targetNode];
    }

    void removeNode(T node) {
        auto& edges = nodes[node];
        for (const auto& [targetNode, weight]: edges) {
            nodes[targetNode].erase(node);
        }
        nodes.erase(node);
    }

    auto begin() {return nodes.begin();}
    auto end() {return nodes.end();}


private:
    std::unordered_map<T, std::unordered_map<T, W>> nodes;
};

