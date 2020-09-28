//
// Created by vincent on 9/20/20.
//

#ifndef VSTL_RBTREE_H
#define VSTL_RBTREE_H

#include <memory>

#define NIL nullptr

namespace cpstl {

    template<class T>
    struct Node {
        Node<T> *parent = NIL;
        Node<T> *left = NIL;
        Node<T> *right = NIL;
        bool red = false;
        T key;

        Node(T value){
            this->key = value;
        }
    };

    template <class T>
    class RBTree {

    private:
        Node<T> *root;

        //Method
        void left_rotation(Node<T> *&value);

        void right_rotation(Node<T> *&value);

        void rb_insert_fixup(Node<T> *&root, Node<T> *&new_node);

        Node<T> *search_value_rb(Node<T> *&node, T value);

    public:
        RBTree(const T &value){
            this->root = new Node<T>(value);
        }

        ~RBTree() {
           delete root;
        }

        void insert_node(T value);

        void delete_node(T value);

        Node<T> *search_value(T value);

        inline Node<T> *get_root()
        {
            return this->root;
        }

        T max_value();

        T min_value();
    };
};

#endif //VSTL_RBTREE_H
