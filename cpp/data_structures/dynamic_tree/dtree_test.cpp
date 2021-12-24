#include "./dynamic_tree.hpp"

    // just a simple tests for dynamic tree "functionality"
int main() {

    // create dynamic tree
    cpstl::DynamicTree<int> dtree("root",1);

    // insert new nodes & check
    if(!dtree.current_node->insert("a3",1)) std::cout << "insert error !!! \n";
    if(!dtree.current_node->insert("a2",2)) std::cout << "insert error !!! \n";
    
    // move and insert
    dtree.go_to("a3");
    if(!dtree.current_node->insert("g2",3)) std::cout << "insert error !!! \n";
    if(!dtree.current_node->insert("g4",4)) std::cout << "insert error !!! \n";
    
    // move and insert
    dtree.go_to("g2");
    if(!dtree.current_node->insert("ab4",4)) std::cout << "insert error !!! \n";
    if(!dtree.current_node->insert("ab5",5)) std::cout << "insert error !!! \n";

    // jump to root
    if(dtree.go_to_root()) std::cout << "moved to root sucessed !\n";

    // test path
    std::vector<std::string> path = {"a3","g4"};

    // move and check
    if(dtree.go_to( "a3" )) std::cout << "go_to sucessed !\n";
    else  std::cout << "go_to unsucessed !\n";
    
    // print values => where current node right now 
    std::cout << dtree.current_node->name << " " << dtree.current_node->value << "\n";

    // remove all children
    dtree.current_node->removeChildren();

    // jump to root
    if(dtree.go_to_root()) std::cout << "moved to root sucessed !\n";

    // try to travel from root to "g4" using path
    if(dtree.travel_to( path )) std::cout << "travle sucessed !\n";
    else  std::cout << "travle unsucessed !\n";
    
    // print values => where current node right now 
    std::cout << dtree.current_node->name << " " << dtree.current_node->value << "\n";

    return 0;
}
