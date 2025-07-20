#include <iostream>
#include <memory>
#include <list>


template<typename T>
class LinkedTree {
public:
    template<typename S>
    class Node{
        friend class LinkedTree<S>;
        S info;
        Node<S>* parent = nullptr;
        std::list<std::shared_ptr<Node<T>>> children = nullptr;
        bool operator==(Node<S> rhs) {
            return ((info == rhs.info) && (parent == rhs.parent) && (children == rhs.children));
        }
    };

    LinkedTree(): root(nullptr) {}
    LinkedTree(Node<T>* node): root(std::shared_ptr(node)) {}

    bool isEmpty() {return root == nullptr;}

    Node<T>* getRoot() {return root.get();}
    T getElement(Node<T>* node) {return node->info;}
    Node<T>* getParent(Node<T>* node) {return node->parent;}

    bool isRoot(Node<T>* node) {return operator==(node);}
    bool isLeaf(Node<T>* node) {return node->children.size() == 0;}
    bool isInternal(Node<T>* node) {return !isLeaf();}

    Node<T>* add(T e, Node<T>* parent = nullptr) {
        if (parent == nullptr && root != nullptr) {
            printf("Root no vacio");
        } else if (root == nullptr) {
            auto root = std::make_shared<Node<T>>(e, parent, nullptr);
            return root.get();
        } else {
            auto aux = std::make_shared<Node<T>>(e, parent);
            parent->children.push_front(aux);
            return aux.get();
        }
        return nullptr;
    }

    std::list<std::shared_ptr<Node<T>>> getChildren(Node<T>* node) {return node->children;}

    LinkedTree<T> cut(Node<T>* node) {
        auto parent = node->parent;
        if (parent) {
            parent->children.remove(node);
            node->parent = nullptr;
        }
        return LinkedTree(node);
    }

    void attach(Node<T>* node, LinkedTree<T> subt) {
        auto subroot = subt.getRoot();
        subroot->parent = node;
        node->children.push_front(subroot);
    }

private:
    std::shared_ptr<Node<T>> root = nullptr;
};

