#include <iostream>
#include <memory>

template<typename T>
class LCRSTree {
public:
    template<typename S>
    class Node {
        friend class LCRSTree;
        S info;
        Node<S>* parent;
        std::shared_ptr<Node<T>> leftChild;
        std::shared_ptr<Node<T>> rightSibling;
        auto operator==(Node<T> rhs) {
            return (rhs.info == info) && (rhs.parent == parent )
            && (rhs.leftChild == leftChild) && (rhs.rightSibling == rightSibling);
        }
    };
    template<typename S>
    class ChildIterator {
    public:
        ChildIterator(std::shared_ptr<Node<S>> node) : it(node) {}

        ChildIterator& operator++() {
            it = it->rightSibling;
            return *this;
        }

        ChildIterator operator++(int) {
            auto tmp = *this;
            operator++();
            return tmp;
        }

        auto operator*() {
            return it;
        }

        auto operator!=(const ChildIterator& other) {
            return other.it != it;
        }

    private:
        std::shared_ptr<Node<S>> it;
    };

    template<typename S>
    class ChildIterable {
    public:
        
        ChildIterable(Node<S>* n): node(n) {}
        auto begin() {return ChildIterator(node);}
        auto end() {return ChildIterator(nullptr);}

    private:
        std::shared_ptr<Node<S>> node;
    };

    LCRSTree(): root(nullptr) {}
    LCRSTree(std::shared_ptr<Node<T>> node): root(node) {}

    ChildIterable<T> getChildren(Node<T>* node) {return ChildIterable<T>(node->leftChild);}
    
    Node<T>* getRoot() {return root.get();}
    T getElement(Node<T>* node) {return node->info;}
    Node<T>* getParent(Node<T>* node) {return node->parent;}
    
    bool isEmpty() {return root == nullptr;}
    bool isRoot(Node<T>* node) {return operator==(node);}
    bool isLeaf(Node<T>* node) {return node->leftChild == nullptr;}
    bool isInternal(Node<T>* node) {return !isLeaf(node);}
    
    auto addChild(T e, Node<T>* parent) {
        if (parent == nullptr && root != nullptr) {
            printf("Root no vacio, error");
        } else if (parent == nullptr) {
            root = std::make_shared<Node<T>>();
            root->info = e;
            root->parent = parent;
            root->rightSibling = nullptr;
            root->leftChild = nullptr;
            return root.get();
        } else {
            auto newNode = std::make_shared<Node<T>>(e, parent, nullptr, nullptr);
            if (parent->leftChild == nullptr) {
                parent->leftChild = newNode;
            } else {
                auto c = parent->leftChild;
                while (c->rightSibling != nullptr) {
                    c = c->rightSibling;
                }
                c->rightSibling = newNode;
            }
            return newNode.get();
        }
        return nullptr;
    }

    LCRSTree<T> cut(Node<T>* node) {
        if (node) {
            auto parent = getParent(node);

            if (parent) {
                if (parent->leftChild.operator==(node)) {
                    parent->leftChild = node->rightSibling;
                } else {
                auto sibling = parent->leftChild;
                while (!sibling->rightSibling.operator==(node)) {
                    sibling = sibling->rightSibling;
                }
                sibling->rightSibling = sibling->rightSibling->rightSibling;
                }
                node->parent = nullptr;
                node->rightSibling = nullptr;
            }
        return LCRSTree<T>(node);
    }
    
    
/*


    attach

*/
private:
    std::shared_ptr<Node<T>> root = nullptr;
};


int main() {

    return 0;
}

