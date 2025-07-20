#include <iostream>
#include <unordered_map>
#include <vector>

template <typename T, typename W>
class BasicGraph {
public:
    void addNode(T node) {
        nodes[node] = {};
    }

    void setEdge(T sourceNode, T targetNode, W weight) {
        nodes[sourceNode][targetNode] = weight;
        nodes[targetNode][sourceNode] = weight; // Grafo no dirigido
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
        for (const auto& [targetNode, weight] : edges) {
            nodes[targetNode].erase(node);
        }
        nodes.erase(node);
    }

    auto begin() {return nodes.begin();}
    auto end() {return nodes.end();}

private:
    std::unordered_map<T, std::unordered_map<T, W>> nodes;
};


int main() {
    BasicGraph<int, int> graph;

    // Agregar nodos
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addNode(5);

    // Agregar aristas
    graph.setEdge(1, 2, 42);
    graph.setEdge(1, 3, 43);
    graph.setEdge(1, 4, 44);
    graph.setEdge(1, 5, 44);
    graph.setEdge(2, 3, 37);
    graph.setEdge(3, 4, 34);
    graph.setEdge(4, 5, 54);

    // Mostrar grafo completo
    for (const auto& [node, edges] : graph) {
        std::cout << "Aristas del nodo " << node << ":" << "\n";
        for (const auto& [targetNode, weight] : edges) {
            std::cout << "  - Nodo " << targetNode << ": " << ((weight != 0) ? "Conectado" : "No conectado") << "\n";
        }
    }

    graph.removeNode(3);

    std::cout << "***********************\n";

    // Mostrar grafo sin nodo 3
    for (const auto& [node, edges] : graph) {
        std::cout << "Aristas del nodo " << node << ":" << "\n";
        for (const auto& [targetNode, weight] : edges) {
            std::cout << "  - Nodo " << targetNode << ": " << ((weight != 0) ? "Conectado" : "No conectado") << "\n";
        }
    }

    std::cout << "***********************\n";

    // GetEdges muestra la arista si existe y sino la crea "vacia"
    std::cout << "Node 1 - Node 2: " << graph.getEdge(1, 2) << "\n";
    std::cout << "Node 2 - Node 5: " << graph.getEdge(2, 5) << "\n";

    return 0;
}