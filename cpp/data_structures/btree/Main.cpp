//
// Created by vincent on 9/20/20.
//

#include <memory>
#include <iostream>
#include "BTree.h"

//TODO this looks like a c implementation!!

template <class T>
void print_level_tree(const struct btree::Node<T> *root, std::string elem);


int main()
{
    auto root = std::make_unique<btree::Node<int>>();
    root->value = 50;
    btree::insert_node<int>(root.get(), 30);
    btree::insert_node<int>(root.get(), 24);
    btree::insert_node<int>(root.get(), 5);
    btree::insert_node<int>(root.get(), 28);
    btree::insert_node<int>(root.get(), 45);
    btree::insert_node<int>(root.get(), 98);
    btree::insert_node<int>(root.get(), 51);
    btree::insert_node<int>(root.get(), 60);

    std::cout << "-------- Insert -----------" << std::endl;
    print_level_tree(root.get(), "Root");

    /*std::cout << "-------- delete -----------" << std::endl;
    btree::delete_node(root.get(), 2);
    btree::delete_node(root.get(), 10);
    print_level_tree(root.get());*/


    root.release();
}

//TODO improve this method!
template <class T>
void print_level_tree(const struct btree::Node<T> *root, std::string elem)
{
    if (root == NULL)
        return;

    std::cout << elem << " " << root->value << std::endl;

    if(root->left)
        print_level_tree(root->left, "left");

    if(root->right)
        print_level_tree(root->right, "right");
}