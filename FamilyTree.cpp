#include "FamilyTree.hpp"

namespace family{

    family::Tree::Tree(const std::string rootName) : root(rootName) {
        this->root->relation = "me";
        this->root->rank=0; 
    }

    Tree& Tree::addFather(const std::string sonName, const std::string fatherName) {
	    Node sonNode = recursiveGetAncestorNode(this->root , sonName);
		Node *father = new Node;
        father->child = sonNode;
        father->rank = sonNode->rank+1;
        father->name = fatherName;
        if(father->rank==1)
            father->relation = "father";
        else if(father->rank==2)
            father->relation = "grandfather";
        else if(father->rank>2){
            father->relation = "grandfather";
            std::string tmpName = "";
            for (int i = 2; i < father->rank; i++){
                tmpName = "great-"+tmpName;
            }
            father->relation = tmpName+father->relation;
        }
        sonNode->father= father;			
        return *this;
    }

    Tree& Tree::addMother(const std::string sonName, const std::string motherName) {
        Node sonNode = recursiveGetAncestorNode(this->root , sonName);
        Node *mother = new Node;
        mother->child = sonNode;
        mother->rank = sonNode->rank+1;
        mother->name = motherName;
        if(mother->rank==1)
            mother->relation = "mother";
        else if(mother->rank==2)
            mother->relation = "grandmother";
        else if(mother->rank>2){
            mother->relation = "grandmother";
            std::string tmpName = "";
            for (int i = 2; i < mother->rank; i++){
                tmpName = "great-"+tmpName;
            }
            mother->relation = tmpName+mother->relation;
        }
        sonNode->mother= mother;
        return *this;
    }

    void Tree::display() {
    }

    std::string Tree::find(const std::string relation2Root) {
        return "";
    }

    std::string Tree::relation(const std::string ancestorName) {
        return "";
    }

    Tree& Tree::remove(const std::string name) {
        Node removeNode = recursiveGetAncestorNode(this->root , name);
        if (removeNode->rank==0)
            throw(std::runtime_error("error"));
        remove(removeNode->father->name);
        remove(removeNode->mother->name);
        if(removeNode->child->father->name.compare(name) == 0){
            removeNode->child->father = NULL;
        }
        else{
            removeNode->child->mother = NULL;
        }
        delete removeNode;
        return *this;
    }
	
    Node& recursiveGetAncestorNode(const node &rootNode, string ancestorName){
    	if(rootNode.name == ancestorName)
    		return rootNode;
    	node& ancestorNode;
    	if(rootNode->father != NULL){
    		ancestorNode = recursiveGetAncestorNode(rootNode->father, ancestorName);
    		if(ancestorNode != NULL)
    			return &ancestorNode;
    	}
    	if(rootNode->mother != NULL){
    		ancestorNode = recursiveGetAncestorNode(rootNode->mother, ancestorName);
    		if(ancestorNode != NULL)
    			return &ancestorNode;
    	}
		throw(std::runtime_error("error"));

    }
}

	// string relation (const string ancestorName){
		// node ancestorNode = recursiveGetAncestorNode(this.root, ancestorName);
		// if(ancestorNode == NULL)
			// return "unrelated";
		// return ancestorNode.name;
	// }
    


