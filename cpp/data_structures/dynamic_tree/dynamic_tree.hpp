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

            // o(log n) 
            // search for children node in current node
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
            
            // o(log n) 
            // search for children in temp node
            int binary_search(std::string const& target_name , std::shared_ptr<DT_Node<V>> temp) {
                int min = 0;
                int max = temp->children.size() - 1;
                int mid = (min + max) / 2;

                while (min <= max) {

                    // in case target found
                    if (temp->children[mid]->name == target_name) {
                        return mid;
                    }

                    // going left
                    if (temp->children[mid]->name.compare(target_name) > 0) {
                        max = (mid - 1);
                    }

                    // going right
                    if (temp->children[mid]->name.compare(target_name) < 0) {
                        min = (mid + 1);
                    }

                    // update mid
                    mid = (min + max) / 2;
                }

                // in case not found
                return -1;
            }

            // o(1) 
            // function take a "temp node" & make a simple check if that temp include a parent with specific name
            // return => "parent pointer" or NULL
            std::shared_ptr<DT_Node<V>> search_up(std::string& parent_name, std::shared_ptr<DT_Node<V>> temp) {

                if (temp->parent != NULL && temp->parent->name == parent_name) {
                    return temp->parent;
                }
                else return NULL;

            }

            // o(1) --> o(log n) 
            // like "search_up" function , but this one for looking "down" between children
            std::shared_ptr<DT_Node<V>> search_down(std::string& child_name , std::shared_ptr<DT_Node<V>> temp) {

                // o(log n)
                // search for target 
                int index = this->binary_search(child_name,temp);

                if (index != -1) {
                    return temp->children[index];
                }

                return NULL;
            }


            // o(path) --> o(log n * path)
            /*
                like go_to but this require a hole path of "names" in one direction
                note !! travel will happend only if "the whole path of names" is valid
                otherwise nothing will be happen & return will be false
            */
            bool travel(std::vector<std::string> const& path_of_names, bool up = false) {

                // temp only for "check & test" if "path_of_names" are valid or not
                // if "path_of_names" is valid we make it the new current_position "as last step" 
                // else nothing will be happen
                std::shared_ptr<DT_Node<V>> temp = current_node;

                // up true => mean that "path_of_names" in parents direction "up"
                if (up) {

                    // o(path)
                    // we start looking up by using a private function "search_up"
                    for (std::string target_name : path_of_names) {

                        // o(log n)
                        temp = search_up(target_name, temp);

                        // in case not found "that's mean invalid path"
                        if (temp == NULL) return false;
                    }

                }
                // "up == false" mean that "path_of_names" in children direction "down"
                else {

                    // o(path)
                    // we start looking down by using a private function "search_down"
                    for (std::string target_name : path_of_names) {

                        // o(log n)
                        temp = search_down(target_name, temp);

                        // in case not found "that's mean invalid path"
                        if (temp == NULL) return false;
                    }

                }

                // in case "path_of_names" is valid 
                // last step => travel/jump from "current_position" to "temp node"
                this->current_node = temp;

                // and confirmation 
                return true;
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

            // travel in parent's direction   "up"
            bool travel_up(std::vector<std::string> const&  path_of_names) {
                return this->travel(path_of_names, true);
            }

            // travel in child's direction    "down"
            bool travel_down(std::vector<std::string> const& path_of_names) {
                return this->travel(path_of_names, false);
            }

            // just for testing 
            void print() {

                int i = 0;
                std::cout << "================\n";
                std::cout <<"== " << this->current_node->name << '\n';
                for(std::shared_ptr<DT_Node<V>> node : current_node->children) {
                    std::cout << "---->[" << i << "] " << node->name << " : " << node->value << '\n';
                    i += 1;
                }
                std::cout << "================\n";

            }
            
    }; // end of "Dynamic Tree" Class 

} // end of "cpstl" namespace 

#endif