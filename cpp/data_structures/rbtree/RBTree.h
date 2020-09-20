//
// Created by vincent on 9/20/20.
//

#ifndef VSTL_RBTREE_H
#define VSTL_RBTREE_H

namespace rbtree {

    //Interface of the rbthree
    template<class T>
    struct Node {
        Node<T> *left = nullptr;
        Node<T> *right = nullptr;
        bool red = false;
        T value;
    };

    template <typename T>
    bool insert_node(struct Node<T> &node);

    template <typename T>
    bool delete_node(Node<T> &node);

    template <typename T>
    Node<T> get_node(T key);
};

#endif //VSTL_RBTREE_H
