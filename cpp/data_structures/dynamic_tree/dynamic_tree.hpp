#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>

#pragma once

#ifndef DYNAMIC_TREE_H
#define DYNAMIC_TREE_H

namespace cpstl {

    // ===================
    // === Nodes class ===
    // ===================
    template<typename T>
    class DT_Node {

        private:
            // parent of this node 
            std::shared_ptr<DT_Node<T>> parent;

            // node name => each node must have a name for dealing with it => "search , sort , ..."
            std::string name;

        public:
            // children of this node 
            std::vector< std::shared_ptr<DT_Node<T>> > children;

            // node value
            T value;

            // default constructor
            DT_Node() {}


            DT_Node( std::string node_name, T node_value, std::shared_ptr<DT_Node<T>> parent_node = NULL )
                :   name{ node_name },
                    value{ node_value },
                    parent{ parent_node } 
            { }

            ~DT_Node() { }

            std::string get_name() {
                return this->name;
            }

            // giving access to DynamicTree class to control each node
            template<typename T> friend class DynamicTree;
    }; // end of Dynamic Tree Class 




    // =========================
    // === DynamicTree class ===
    // =========================
    template<typename V> 
    class DynamicTree {

        private:
            // main node in DynamicTree
            std::shared_ptr<DT_Node<V>> root;

            bool binary_search(std::string const& target_name, int& target_index) {
                int min = 0;
                int max = current_node->children.size() - 1;
                int mid = (min + max) / 2;

                while (min <= max) {

                    // in case target found
                    if (current_node->children[mid]->name == target_name) {
                        if (&target_index != NULL) {
                            target_index = mid;
                        }
                        return true;
                    }

                    // going left
                    if (current_node->children[mid]->name.compare(target_name) > 0) {
                        max = (mid - 1);
                    }

                    // going right
                    if (current_node->children[mid]->name.compare(target_name) < 0) {
                        min = (mid + 1);
                    }

                    // update mid
                    mid = (min + max) / 2;
                }

                // in case not found
                if (&target_index != NULL) {
                    target_index = -1;
                }
                return false;
            }

        public:

            // current_node => it's a node represent you position in tree
            // "important !" for many operation like search , movement , ...
            std::shared_ptr<DT_Node<V>> current_node;

            // constructor
            DynamicTree(std::string root_name, V root_value) {
                // parent of root must be null
                root = std::make_shared<DT_Node<V>>(root_name, root_value);
                current_node = root;
            }

            ~DynamicTree() {

            }

            // o( (n log n) + (log n) + 1 )
            // duplicate names are not allowed here in dynamic tree
            bool insert(std::string const new_node_name, V const new_node_value) {

                // just int for required parameter in search function
                int fake_index = -1;

                // o(log n)
                // first we check if any node is already exist with the same name
                if (search_for_index(new_node_name, fake_index)) return false;

                // then
                // insert new child
                this->current_node->children.push_back( 
                    std::make_shared<DT_Node<V>>(new_node_name, new_node_value, current_node)
                );

                // o(n log n)
                // sort children
                this->sort();

                // confirmation
                return true;
            }

            // target_index : useful if you want to get index of that target in case not found you get -1
            bool search_for_index(std::string const target_name, int& target_index) {
                return this->binary_search(target_name, target_index);
            }

            // sort children of this current node
            // o(n log n) --> o(n²)
            void sort() {

                std::sort(current_node->children.begin(), current_node->children.end(),
                    // comparison function
                    [&](std::shared_ptr<DT_Node<V>> &a, std::shared_ptr<DT_Node<V>> &b) {
                        return ( a->name < b->name );
                    }
                );
               
            }
            
            // o(1) --> o(log n)
            // target_child_name => mean sub node where you want to go
            bool go_to(std::string const& target_child_name) {

                // search for target index
                int index = -1;
                this->search_for_index(target_child_name, index);

                // in case target found
                if (index != -1) {

                    this->current_node = this->current_node->children[index];
                    return true;

                }

                // in case target 'not found'
                return false;
            }

            // o(1)
            // go from this current_node to its parent node
            bool go_back() {

                // if parent not NULL
                if (this->current_node->parent != NULL) {
                    // move to parent
                    this->current_node = this->current_node->parent;

                    return true;
                }

                // else mean parent found
                return false;
            }


            // o(1)
            // go to the root directly 
            bool go_to_root() {

                // if parent of current node is NULL that mean current node already in root
                if (this->current_node->parent == NULL) return false;

                // else
                this->current_node = this->root;
                return true;
            }

            // just for testing 
            void print() {

                int i = 0;
                std::cout << "================\n";
                std::cout <<"== " << this->current_node->name << '\n';
                for (std::shared_ptr<DT_Node<V>> node : current_node->children) {
                    std::cout << "---->[" << i << "] " << node->name << " : " << node->value << '\n';
                    i += 1;
                }
                std::cout << "================\n";

            }
            
    }; // end of "Dynamic Tree" Class 

} // end of "cpstl" namespace 

#endif