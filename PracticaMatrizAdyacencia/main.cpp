#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

struct City {
    std::string name{};
    int population{};
    float surface{};

    using ID = std::string;

    ID getID() {return name;}

    auto operator<=>(const City& rhs) const = default;
};

// Necesario para usar una tabla hash con un tipo definido por el usuario
template <>
struct std::hash<City> {
    std::size_t operator()(const City& city) const {
        return (std::hash<std::string>()(city.name));
    }
};

// Para poder imprimir ciudades con std::cout
std::ostream& operator<<(std::ostream& os, const City& rhs) {
    os << "Nombre: " << rhs.name << "\n";
    os << "Población: " << rhs.population << "\n";
    os << "Superficie: " << rhs.surface << " km²\n";  // el 2 del cuadrado puede dar problemas, que lo borren si es así
    return os;
}

#include <set>
#include <list>

template <typename T, typename W>
class ObjectGraph {
public:

    void anchura(T node) {
        std::stack<typename T::ID> pila;
        pila.push(node);
        std::set<typename T::ID> visitados;
        std::list<typename T::ID> sol;
        // inserta sus
        while (!pila.empty()) {
            T n = pila.pop();
            if (visitados.find(n) == visitados.end()) {
                pila.push(n);
                sol.push_back(n);// insertar en la lista solucion por el final
                pila.push();// insertar en sus adyacentes en la pila
            }
        }
        return sol; // devolver lista solucion
    }

    void profundidad() {}

    void addNode(T node) {
        nodes[node.getID()] = {};
        reverse[node.getID()] = node;
    }

    void setEdge(T sourceNode, T targetNode, W weight) {
        nodes[sourceNode.getID()][targetNode.getID()] = weight;
        nodes[targetNode.getID()][sourceNode.getID()] = weight; // Grafo no dirigido
    }

    void setEdge(typename T::ID sourceNode, typename T::ID targetNode, W weight) {
        nodes[sourceNode][targetNode] = weight;
        nodes[targetNode][sourceNode] = weight; // Grafo no dirigido
    }

    const std::unordered_map<typename T::ID, W>& getEdges(T node) const {
        return nodes[node.getID()];
    }

    const std::unordered_map<typename T::ID, W>& getEdges(typename T::ID node) const {
        return nodes[node];
    }

    // No puede ser const porque puede crear la arista vacia si no existe
    W getEdge(T sourceNode, T targetNode) {
        return nodes[sourceNode.getID()][targetNode.getID()];
    }

    // No puede ser const porque puede crear la arista vacia si no existe
    W getEdge(typename T::ID sourceNode, typename T::ID targetNode) {
        return nodes[sourceNode][targetNode];
    }

    void removeNode(T node) {
        auto& edges = nodes[node.getID()];
        for (const auto& [targetNodeId, weight] : edges) {
            nodes[targetNodeId].erase(node.getID());
        }
        nodes.erase(node.getID());
        reverse.erase(node.getID());
    }

    void removeNode(typename T::ID node) {
        auto& edges = nodes[node];
        for (const auto& [targetNodeId, weight] : edges) {
            nodes[targetNodeId].erase(node);
        }
        nodes.erase(node);
        reverse.erase(node);
    }

    T& getNode(typename T::ID nodeId) {return reverse[nodeId];}

    auto begin() {return nodes.begin();}
    auto end() {return nodes.end();}

private:
    std::unordered_map<typename T::ID, std::unordered_map<typename T::ID, W>> nodes;
    std::unordered_map<typename T::ID, T> reverse;
};


int main() {
    // El ' en los numeros es para facilitar la lectura de los miles
    City madrid{"Madrid", 3'332'035, 604.45};
    City barcelona{"Barcelona", 1'660'122, 101.35};
    City paris{"Paris", 2'240'621, 105.4};
    City estrasburgo{"Estrasburgo", 846'450, 78.26};
    City bruselas{"Bruselas", 185'103, 32.61};

    std::cout << madrid << "\n";

    std::cout << "***********************\n";

    ObjectGraph<City, float> cityGraph;

    // Agregar ciudades
    cityGraph.addNode(madrid);
    cityGraph.addNode(barcelona);
    cityGraph.addNode(paris);
    cityGraph.addNode(estrasburgo);
    cityGraph.addNode(bruselas);

    // Agregar distancias
    cityGraph.setEdge(madrid,      barcelona,   627.5);  // puede usarse la variable
    cityGraph.setEdge("Madrid",      "Paris",       1277.0);  // o el nombre (cuidado mayúsculas)
    cityGraph.setEdge(madrid,      estrasburgo, 1653.2);
    cityGraph.setEdge(madrid,      bruselas,    1579.0);
    cityGraph.setEdge(barcelona,   paris,       1035.4);
    cityGraph.setEdge(paris,       estrasburgo, 491.4);
    cityGraph.setEdge(estrasburgo, bruselas,    433.4);

    // Mostrar grafo completo
    for (const auto& [city, conexions] : cityGraph) {
        std::cout << "Conexiones de la ciudad " << city << ":" << "\n";
        for (const auto& [targetCity, distance] : conexions) {
            std::cout << "  - City " << targetCity << ": " << distance << "\n";
        }
    }

    cityGraph.removeNode(paris);

    std::cout << "***********************\n";

    // Mostrar grafo sin paris
    for (const auto& [city, conexions] : cityGraph) {
        std::cout << "Conexiones de la ciudad " << city << ":" << "\n";
        for (const auto& [targetCity, distance] : conexions) {
            std::cout << "  - City " << targetCity << ": " << distance << "\n";
        }
    }

    std::cout << "***********************\n";

    // GetEdges muestra la arista si existe y sino la crea "vacia"
    std::cout << "Madrid - Barcelona: " << cityGraph.getEdge(madrid, barcelona) << "\n";
    std::cout << "Barcelona - Bruselas: " << cityGraph.getEdge(barcelona, bruselas) << "\n";

    std::cout << "***********************\n";


    return 0;
}