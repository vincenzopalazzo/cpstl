//
// Created by vincent on 9/20/20.
//

#ifndef VSTL_RBTREE_H
#define VSTL_RBTREE_H

#include <memory>

namespace cpstl {

    template<class T>
    class Node {
    public:
        Node(T value) : value(value) {}
        Node<T> *parent = nullptr;
        Node<T> *left = nullptr;
        Node<T> *right = nullptr;
        T value;
    };

    template <class T>
    class BTree {
    private:
        Node<T> *root;
        void transplan(Node<T> *&u, Node<T> *&v);
        Node<T> *insert_recursive(Node<T> *&u, T value);
        Node<T> *get_node_recursive(Node<T> *&root, T key);

    public:
        BTree(Node<T> *&root);
        BTree();

        Node<T> *get_root();
        bool insert_node(T value);
        bool delete_node(T value);
        Node<T> *search_node(T value);
        Node<T> *tree_minimum(Node<T> *&node);
        T min();
    };
};

#endif //VSTL_RBTREE_H
