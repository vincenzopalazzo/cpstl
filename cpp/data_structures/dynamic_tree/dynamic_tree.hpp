/*
    Dynamic Tree Node

	-- NAME ---------- BEST --> WORST

	length		    => o(1)

	insert			=> o( (n log n) + (log n) + 1 )
	search			=> o(1) --> o(log n)
	sort            => o(n log n) --> o(n²)

	getCopy        	=> o(1) --> o(log n)
	replace   		=> o(1) --> o(log n)

	remove			=> o(nodes * log n)
    removeChild     => o(log n) --> o(nodes * log n)
    removeChildren  =>

    operator <      => o(1) 
    operator >      => o(1)

*/


/*
    Dynamic Tree 
    
    -- NAME ------	BEST --> WORST
    search_up		o(1)
    search_down		o(1) --> o(log n)

    go_to			o(1) --> o(log n) 
    go_to_root      o(1)
    go_back         o(1)
    travel_to	    o(log n) --> o(log n * path)

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#pragma once

#ifndef DYNAMIC_TREE_H
#define DYNAMIC_TREE_H

namespace cpstl {

    // ================================
    // === Dynamic Tree Nodes class ===
    // ================================
    template<typename t> class DT_Node {

        private:
            // parent of this node 
            DT_Node<t>* parent;

        public:
            // children of this node 
            std::vector<DT_Node<t>> children;
            
            // name => for dealing with nodes "search , sort , ..."
            std::string name;

            // node value
            t value;

            // default constructor
            DT_Node() {}

            // second constructor
            DT_Node(std::string node_name, t node_value , DT_Node<t> *parent_node)
                : name    { node_name }  ,
                  value   { node_value } ,
                  parent  { parent_node }
            { }

            // destructor
            ~DT_Node() { }

            // o( (n log n) + (log n) + 1 )
            // duplicate names are not allowed here in dynamic tree
            bool insert(std::string new_node_name , t new_node_value) {

                // just int for required parameterin search function
                int fake_index = 0;

                // o(log n)
                // first we check if any node is already exist with the same name
                if( search(new_node_name , fake_index) ) return false;
                
                // then
                // insert new child
                children.push_back(DT_Node<t>(new_node_name, new_node_value, this));

                // o(n log n)
                // sort children
                this->sort();

                // confirmation
                return true;
            }

            // o(1) --> o(log n)
            // search => "bineay search" between children
            // target_index : useful if you want to get index of that target in case not found you get -1
            bool search(std::string target_name , int &target_index = NULL){

                int min = 0;
                int max = this->children.size() - 1;
                int mid = ( min + max ) / 2;

                while( min <= max ){

                    // in case target found
                    if(this->children[mid].name == target_name){
                        if(&target_index != NULL) {
                            target_index = mid;
                        }
                        return true;
                    }
                    
                    // going left
                    if(this->children[mid].name.compare(target_name) > 0){
                        max = (mid - 1);
                    }

                    // going right
                    if(this->children[mid].name.compare(target_name) < 0){
                        min = (mid + 1);
                    }

                    // update mid
                    mid = ( min + max ) / 2 ;
                }

                // in case not found
                if(&target_index != NULL) {
                    target_index = -1;
                }
                return false;
            }

            // sort children
            // o(n log n) --> o(n²)
            void sort(bool reverse = false){

                if(reverse){
                    std::sort(this->children.begin() , this->children.end() , 
                        // comparison function
                        [](DT_Node<t> a , DT_Node<t> b){
                            return (a > b);
                        }
                    );
                }
                else{
                    std::sort(this->children.begin() , this->children.end() , 
                        // comparison function
                        [](DT_Node<t> a , DT_Node<t> b){
                            return (a < b);
                        }
                    );
                }

            }

            // o(1) --> o(log n)
            // get a copy of specific child , this copy not connected to the original tree
            // in case target not found return will be a empty node
            DT_Node<t> getCopy(std::string target_node_name){
                
                int index = -1;

                // search for target
                this->search(target_node_name,index);

                // temp copy
                DT_Node<t> copy_of_child;

                // in case target found
                if(index != -1){
                    // set name & value using index
                    copy_of_child.name  = this->children[index].name;
                    copy_of_child.value = this->children[index].value;
                }

                return copy_of_child;
            }

            // o(log n) --> o(nodes * log n)
            // remove child with specific name with his all children
            bool removeChild(std::string target_node_name){

                // search for target index
                int index = -1;
                search(target_node_name , index);

                // call recursive remove of this child node
                if(index != -1){
                    children[index].removeChildren();
                    children.erase(children.begin() + index);
                    return true;
                } 

                return false;
            }

            // like removeChild function but this for all children 
            void removeChildren(){
                
                // nested recursive removeChildren => remove all children of children
                for(DT_Node<t> &child : this->children){
                    child.removeChildren();
                }

                // last step remove children by setup a new empty vector 
                this->children = std::vector<DT_Node<t>>();
            }

			// testing function
			void print(){
                std::cout << "==================================" << '\n'; 
				for(DT_Node<t> &child : this->children){
					std::cout << child.name << "=" << child.value << " "; 
				}
                std::cout << "\n==================================\n"; 
			}

            // get length of children in this node
            unsigned int length(){
                return this->children.size();
            }

            // < comparison operator between tow nodes
            bool operator < (DT_Node<t> &another_node){
                return ( this->name.compare(another_node.name) < 0 ) ? true : false;
            } 

            // > comparison operator between tow nodes
            bool operator > (DT_Node<t> &another_node){
                return ( this->name.compare(another_node.name) > 0 ) ? true : false;
            }

            // giving a access for making some processes like go_to , travel_to ... 
            template<typename v> friend class DynamicTree;
    };

 

    // =========================
    // === DynamicTree class ===
    // =========================
    template<typename v> class DynamicTree {

        private:

            // main node in DynamicTree
            DT_Node<v> root;

            /* 
                **** some private function **** 
                used in "travel_to" function
            */

            // o(1) 
            // function take a "temp node" & make a simple check if that temp include a parent with specific name
            // return will be a "parent pointer" or NULL
            DT_Node<v>* search_up(std::string &parent_name , DT_Node<v>* temp) {
                
                if(temp->parent != NULL && temp->parent->name == parent_name) {
                        return temp->parent;
                }
                else return NULL;

            }

            // o(1) --> o(log n) 
            // like "search_up" function , but this one for looking "down" between children
            DT_Node<v>* search_down(std::string &node_name , DT_Node<v>* temp) {
                
                // o(log n)
                // search for target 
                int index = -1;
                temp->search(node_name , index);
                
                if(index != -1){
                    return &temp->children[index];
                }

                return NULL;
            }

        public:

            // current_node => it's a node represent you position in tree
            // "important !" for many operation like search , movement , ...
            DT_Node<v> *current_node;

            // constructor
            DynamicTree(std::string root_name , v root_value) {
                // parent of root must be null
                root = DT_Node<v>( root_name , root_value , NULL ); 
                current_node = &root;
            }

            // destructor
            ~DynamicTree(){  }

            // o(1) --> o(log n)
            // target_child_name => mean node where you want to go
            bool go_to(const std::string &target_child_name) {

                // search for target index
                int index = -1;
                this->current_node->search(target_child_name,index);

                // in case target found
                if(index != -1){
                    this->current_node = &(this->current_node->children[index]);

                    return true;
                }

                // in case target 'not found'
                return false;
            }

            // o(1)
            // go from this current_node to parent node
            bool go_back(){

                // if parent not NULL
                if(this->current_node->parent != NULL){
                    // move to parent
                    this->current_node = this->current_node->parent;

                    return true;
                }
                // else 
                return false;
            }

            // o(1)
            // go to the root directly 
            bool go_to_root(){
                
                // if parent of current node is NULL that mean current node already in root
                if(this->current_node->parent == NULL) return false;
                
                // else
                this->current_node = &this->root;
                return true;
            }

            // o(path) --> o(log n * path)
            /* 
                like go_to but this require a hole path of "names" in one direction
                note !! travel will happend only if "the whole path of names" is valid 
                otherwise nothing will be happen & return will be false
            */
            bool travel_to(const std::vector<std::string> &path_of_names , bool up = false){
                
                // temp only for "check & test" if "path_of_names" are valid or not
                // if "path_of_names" is valid we make it the new current_position "as last step" 
                // else nothing will be happen
                DT_Node<v>* temp = current_node;

                // up true => mean that "path_of_names" in parents direction "up"
                if(up){

                    // o(path)
                    // we start looking up by using a private function "search_up"
                    for(std::string path : path_of_names){

                        // o(log n)
                        temp = search_up(path , temp);

                        // in case not found "that's mean invalid path"
                        if(temp == NULL) return false;
                    }

                }
                // "up == false" mean that "path_of_names" in children direction "down"
                else{

                    // o(path)
                    // we start looking down by using a private function "search_down"
                    for(std::string path : path_of_names){

                        // o(log n)
                        temp = search_down(path , temp);

                        // in case not found "that's mean invalid path"
                        if(temp == NULL) return false;
                    }

                }

                // in case "path_of_names" is valid 
                // last step => travel/jump from "current_position" to "temp node"
                current_node = temp;

                // and confirmation 
                return true;
            }

    }; // end of Dynamic Tree Class


} // end of namespace

#endif