//
// Created by vincent on 9/20/20.
//

#include <memory>
#include <iostream>
#include "BTree.h"

template <class T>
void print_level_tree(const btree::Node<T> *root, std::string elem);


int main()
{
    btree::BTree<int> tree;
    tree.insert_node(50);
    tree.insert_node(102);
    tree.insert_node(49);

    std::cout << "-------- Insert -----------" << std::endl;
    print_level_tree(tree.get_root(), "Root");

    std::cout << "-------- delete -----------" << std::endl;
    tree.delete_node(49);
    print_level_tree(tree.get_root(), "Root");
}

template <class T>
void print_level_tree(const btree::Node<T> *root, std::string elem)
{
    if (root == nullptr)
        return;

    std::cout << elem << " " << root->value << std::endl;

    if(root->left)
        print_level_tree(root->left, "left");

    if(root->right)
        print_level_tree(root->right, "right");
}