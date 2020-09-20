//
// Created by vincent on 9/20/20.
//

#ifndef VSTL_RBTREE_H
#define VSTL_RBTREE_H

namespace btree {

    //Interface of the rbthree
    template<class T>
    struct Node {
        Node<T> *parent = nullptr;
        Node<T> *left = nullptr;
        Node<T> *right = nullptr;
        T value;
    };

    template<class T>
    bool insert_node(struct Node<T> *root, T value);

    template<class T>
    bool delete_node(Node<T> *root, T value);

    template<class T>
    Node<T> *get_node(Node<T> *root, T key);
};

#endif //VSTL_RBTREE_H
