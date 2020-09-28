//
// Created by vincent on 9/20/20.
//
#include <assert.h>
#include <iostream>
#include "RBTree.h"

using namespace cpstl;

template<class T>
T RBTree<T>::max_value() {
    Node<T> *max = this->root;
    while (max->right) {
        max = max->right;
    }
    return max->key;
}

template<class T>
T RBTree<T>::min_value() {
    Node<T> *min = this->root;
    while (min->left) {
        min = min->left;
    }
    return min->key;
}

template<class T>
void RBTree<T>::insert_node(T value)
{
    Node<T> *z = new Node<T>(value);
    Node<T> *y = NIL;
    Node<T> *x = this->root;
    while (x != NIL) {
        y = x;
        if (value < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NIL) {
        this->root = z;
    } else if (value < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->red = true; // All new node insert inside the RB tree are red
    if (z->parent->parent != NIL)
        rb_insert_fixup(this->root, z);
}


template<class T>
void RBTree<T>::rb_insert_fixup(Node<T> *&root, Node<T> *&new_node) {
    std::cout << "New node " << new_node->key;
    while (new_node->parent != NIL && new_node->parent->red) {
        if (new_node->parent == new_node->parent->parent->left) {
            Node<T> *y = new_node->parent->parent->right;
            if (y->red) {
                new_node->parent->red = false;
                y->red = false;
                new_node->parent->parent->red = true;
                new_node = new_node->parent->parent;
            } else{
                if (new_node->key == new_node->parent->right->key) {
                    new_node = new_node->parent;
                    left_rotation(new_node);
                }
                new_node->parent->red = false;
                new_node->parent->parent->red = false;
                right_rotation(new_node->parent->parent);
            }
        } else {
            Node<T> *y = new_node->parent->parent->left;
            if (y && y->red) {
                new_node->parent->red = false;
                y->red = false;
                new_node->parent->parent->red = true;
                new_node = new_node->parent->parent;
            } else{
                if (new_node == new_node->parent->left) {
                    new_node = new_node->parent;
                    left_rotation(new_node);
                }
                new_node->parent->red = false;
                new_node->parent->parent->red = false;
                right_rotation(new_node->parent->parent);
            }
        }
    }
    this->root->red = false;
}

template<class T>
void RBTree<T>::left_rotation(Node<T> *&value)
{
    Node<T> *child = value->right;
    value->right = child->left;
    if (child->left != NIL) {
        child->left->parent = value;
    }
    child->parent = value->parent;
    if (value->parent == NIL) {
        this->root = child;
    } else if (value->key == value->parent->left->key) {
        value->parent->left = child;
    } else {
        value->parent->right = child;
    }
    child->left = value;
    value->parent = child;
}

template<class T>
void RBTree<T>::right_rotation(Node<T> *&value)
{
    Node<T> *left_child = value->left;
    value->left = left_child->right;
    if (left_child->right != NIL) {
        left_child->right->parent = value;
    }
    left_child->parent = value->parent;
    if (value->parent == NIL) {
        this->root = left_child;
    } else if (value->key == value->parent->right->key) {
        value->parent->right = left_child;
    } else {
        value->parent->right = left_child;
    }
    left_child->right = value;
    value->parent = left_child;
}

template<class T>
Node<T> *RBTree<T>::search_value(T value) {
    return search_value_rb(this->root, value);
}

template<class T>
Node<T> *RBTree<T>::search_value_rb(Node<T> *&node, T value) {
    Node<T> *search = node;
    if (search->key < value) {
        search_value_rb(search->right, value);
    } else if (search->key > value) {
        search_value_rb(search->left, value);
    }
    return search;
}



template class cpstl::RBTree<int>;