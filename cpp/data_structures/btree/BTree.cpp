//
// Created by vincent on 9/20/20.
//
#include "BTree.h"
#include <iostream>
#include <assert.h>

namespace btree {

    template <typename T>
    void transplan(struct Node<T> *u, struct Node<T> *v);

    template <typename T>
    btree::Node<T> *tree_minimum(btree::Node<T> *node);

    template<typename T>
    bool insert_node(struct Node<T> *root, T value) {
        Node<T> *y = nullptr;
        Node<T> *x = root;
        while (x != nullptr) {
            y = x;
            if (value < y->value) {
                //std::cout << "Go to left" << std::endl;
                x = x->left;
            } else {
                //std::cout << "Go to right" << std::endl;
                x = x->right;
            }
        }
        //Never happen with my implementation on three;
        /*if (!y) {
            //Three empty

            root->value = value;
        }*/
        if (value <= y->value){
            y->left = new Node<T>;
            y->left->value = value;
            y->left->parent = y;
        } else {
            //std::cout << "New node" << std::endl;
            y->right = new Node<T>;
            y->right->value = value;
            y->right->parent = y;
        }
        return true;
    }

    template <class T>
    bool delete_node(struct Node<T> *root, T value)
    {
        assert(root != nullptr);
        btree::Node<int> *victim = get_node(root, value);
        if (!victim) return false;
        if (!victim->left)
            transplan(victim, victim->right);
        else if (!victim->right)
            transplan(victim, victim->left);
        else {
            auto y = tree_minimum(victim->right);
            if (y->parent->value != value) {
                transplan(y, y->right);
                y->right = victim->right;
                y->right->parent = y;
            }
            transplan(victim, y);
            y->left = victim->left;
            y->left->parent = y;
        }
        return true;
    }

    template<class T>
    Node<T> *get_node(Node<T> *root, T key)
    {
        if (!root or root->value == key) {
            std::cout << "Find elem\n";
            return root;
        }
        if (key < root->value) {
           return get_node(root->left, key);
        }
        return get_node(root->right, key);
    }

    template <typename T>
    void transplan(struct Node<T> *u, struct Node<T> *v)
    {
        assert(u);
        assert(v);
        if (!u->parent) {
            //Root cases;
            //Bug if remove the last element I need to reset the root with
            //this code I can't do this
            std::cout << "transplan root find";
            u = v;
        } else if (u->parent->left && u->parent->left->value == u->value) {
            std::cout << "left elem find";
            u->parent->left = v;
        } else {
            std::cout << "right elem find";
            u->parent->right = v;
        }
        if (v)
            v->parent = u->parent;
    }

    template <typename T>
    btree::Node<T> *tree_minimum(btree::Node<T> *node)
    {
        assert(node != nullptr && "Node reference null");
        if (node->left)
            node = node->left;
        return node;
    }
}

template class btree::Node<int>;
template bool btree::insert_node<int>(struct Node<int> *root, int value);
template bool btree::delete_node<int>(struct Node<int> *root, int value);
template btree::Node<int> *btree::get_node<int>(struct Node<int> *root, int value);
