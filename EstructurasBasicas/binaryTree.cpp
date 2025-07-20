#include <iostream>
#include <memory>

template<typename T>
class BinaryTree{
public:
    template<typename S>
    class Node {
        friend class BinaryTree<S>;
        S info;
        std::shared_ptr<Node<S>> l;
        std::shared_ptr<Node<S>> r;
        Node<S>* parent;
    };

    auto getRoot() {return root.get();}
    auto getLeftChild(Node<T>* node) {return node->l.get();}
    auto getRightChild(Node<T>* node) {return node->r.get();}
    auto getParent(Node<T>* node) {return node->parent;}

    T getElement(Node<T>* node) {return node->info;}

    auto isRoot(Node<T>* node) {return node == getRoot().get();}
    auto isLeaf(Node<T>* node) {return getLeftChild(node) == nullptr && getRightChild(node) == nullptr;}
    auto isInternal(Node<T>* node) {return !isLeaf(node);}

    Node<T>* addRoot(T e) {
        root = std::make_shared<Node<T>>();
        root->info = e;
        root->parent = nullptr;
        root->l = nullptr;
        root->r = nullptr;
        return root.get();
    }

    Node<T>* addLeftChild(T e, Node<T>* parent) {
        if (parent) {
            auto newNode = std::make_shared<Node<T>>();
            newNode->info = e;
            newNode->parent = parent;
            parent->l = newNode;
            newNode->l = nullptr;
            newNode->r = nullptr;
            return parent->l.get();
        }
        return nullptr;
    }

    Node<T>* addRightChild(T e, Node<T>* parent) {
        if (parent) {
            auto newNode = std::make_shared<Node<T>>();
            newNode->info = e;
            newNode->parent = parent;
            parent->r = newNode;
            newNode->l = nullptr;
            newNode->r = nullptr;
            return parent->r.get();
        }
        return nullptr;
    }

    bool equilibrado(Node<T>* node) {
        auto l = getLeftChild(node);
        auto r = getRightChild(node);

        if (profundidadMax(l) <= profundidadMax(r)+1 ||
            profundidadMax(l) >= profundidadMax(r)-1){
            return true;
        } else {
            return false;

        }


    }

    int profundidadMax(Node<T>* node, int i=0) {
        auto l = getLeftChild(node);
        auto r = getRightChild(node);

        int maxR, maxL = 0;

        if (l != nullptr) {
            if (isLeaf(l)) {
                maxL = profundidadMax(l) + 1;
            } else {
                maxL = profundidadMax(l);
            }
        }


        if (r != nullptr) {
            if (isLeaf(r)) {
                maxR = profundidadMax(r) + 1;
            } else {
                maxL = profundidadMax(r);
            }

        }
        return std::max(maxR, maxL);
    }


private:
    std::shared_ptr<Node<T>> root;
};



int main() {
    BinaryTree<int> t;
    t.addRoot(5);
    auto root = t.getRoot();
    printf("%i", t.getElement(root));
    auto lc = t.addLeftChild(4, root);
    auto rc = t.addRightChild(6, root);
    return 0;
}
