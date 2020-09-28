//
// Created by vincent on 9/20/20.
//

#include <memory>
#include <iostream>
#include "RBTree.h"

using namespace cpstl;

template <class T>
void print_level_tree(const cpstl::Node<T> *root, std::string elem);

int main()
{
    RBTree<int> *root = new RBTree<int>(10);
    std::cout << "-------- Insert -----------" << std::endl;
    root->insert_node(12);
    root->insert_node(13);
    //root->insert_node(11);
    print_level_tree<int>(root->get_root(), "Root");

    /*std::cout << "-------- delete -----------" << std::endl;
    btree::delete_node(root.get(), 2);
    btree::delete_node(root.get(), 10);
    print_level_tree(root.get());*/

    return EXIT_SUCCESS;
}

template <class T>
void print_level_tree(const cpstl::Node<T> *root, std::string elem)
{
    if (root == NIL)
        return;

    std::cout << elem << " " << root->key << std::endl;

    if(root->left)
        print_level_tree(root->left, "left");

    if(root->right)
        print_level_tree(root->right, "right");
}