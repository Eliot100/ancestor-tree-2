#include "FamilyTree.hpp"
#include <exception>
using namespace family;

    Tree& Tree::addFather(std::string sonName,std::string fatherName) {
	Node* sonNode = recursiveGetAncestorNode(this->root , sonName);
	if (sonNode == nullptr || sonNode->name != sonName || sonNode->father != nullptr) {
		throw runtime_error("error");
	}
	Node* father = new Node(fatherName);
        father->child = sonNode;
        father->rank = sonNode->rank+1;
        father->name = fatherName;
        if(father->rank == 1)
            father->relation = "father";
        else if (father->rank == 2)
            father->relation = "grandfather";
        else if (father->rank > 2){
            father->relation = "grandfather";
            std::string tmpName = "";
            for (int i = 2; i < father->rank; i++){
                tmpName = "great-"+tmpName;
            }
            father->relation = tmpName + father->relation;
        }
        sonNode->father = father;
        return *this;
    }

    Tree& Tree::addMother(std::string sonName, std::string motherName) {
        Node* sonNode = recursiveGetAncestorNode(this->root , sonName);
        if ((sonNode->name!=sonName)) { throw runtime_error("la"); }
        if ((sonNode->mother!=(nullptr))) {
            throw runtime_error("lala");
        }
        Node* mother = new Node(motherName);
        mother->child = sonNode;
        mother->rank = sonNode->rank+1;
       	mother->name = motherName;
        if (mother->rank == 1)
            mother->relation = "mother";
        else if (mother->rank == 2)
            mother->relation = "grandmother";
        else if (mother->rank > 2){
            mother->relation = "grandmother";
            std::string tmpName = "";
            for (int i = 2; i < mother->rank; i++){
                tmpName = "great-" + tmpName;
            }
            mother->relation = tmpName + mother->relation;
        }
        sonNode->mother = mother;
        return *this;
    }

    std::string Tree::find( std::string relation2Root) {
	   Node* ancestorNode = nullptr;
    	   ancestorNode = recursiveGetAncestorNodeByRelation(this->root, relation2Root);
	   if(ancestorNode == nullptr)
		   throw std::runtime_error("error");
	   return ancestorNode->name;
    }

    std::string Tree::relation( std::string ancestorName) {
	Node* ancestorNode = recursiveGetAncestorNode(this->root, ancestorName);
        if(ancestorNode == nullptr)
		return "unrelated";
	return ancestorNode->relation;
    }

    Tree& Tree::remove( std::string name) {
        Node* removeNode = recursiveGetAncestorNode(this->root , name);
        if (removeNode == nullptr || removeNode->rank == 0)
            	throw(std::runtime_error("error"));
	if(removeNode->father != nullptr)  {
        	remove2(removeNode->father);
	     	removeNode->father = nullptr;
	}
	if(removeNode->mother != nullptr) {
        	remove2(removeNode->mother);
	     	removeNode->mother = nullptr;
	}
        if(removeNode->child->father->name == name)
            	removeNode->child->father = nullptr;
        else if (removeNode->child->mother->name == name)
            	removeNode->child->mother = nullptr;
	else 
		throw(std::runtime_error("error"));
        delete removeNode;
        return *this;
    }

    void remove2(family::Node *parent) {
	if(parent->father != nullptr)
        	remove2(parent->father);
    	if(parent->mother != nullptr)
        	remove2(parent->mother);
	delete *parent;
    }
	
    Node* recursiveGetAncestorNode(Node* rootNode, std::string ancestorName){
    	if(rootNode->name==ancestorName)
    		return rootNode;
    	Node* ancestorNode = nullptr;
    	if(rootNode->father != nullptr){
    		ancestorNode = recursiveGetAncestorNode(rootNode->father, ancestorName);
    		if(ancestorNode != nullptr)
    			return ancestorNode;
    	}
    	if(rootNode->mother != nullptr){
    		ancestorNode = recursiveGetAncestorNode(rootNode->mother, ancestorName);
    		if(ancestorNode != nullptr)
    			return ancestorNode;
    	}
        return nullptr;
    }

    Node* recursiveGetAncestorNodeByRelation(Node* rootNode, std::string ancestorRelation){
    	if(rootNode->relation==ancestorRelation)
    		return rootNode;
    	Node* ancestorNode = nullptr;
    	if(rootNode->father != nullptr){
    		ancestorNode = recursiveGetAncestorNodeByRelation(rootNode->father, ancestorRelation);
    		if(ancestorNode != nullptr)
    			return ancestorNode;
    	}
    	if(rootNode->mother != nullptr){
    		ancestorNode = recursiveGetAncestorNodeByRelation(rootNode->mother, ancestorRelation);
    		if(ancestorNode != nullptr)
    			return ancestorNode;
    	}
        return nullptr;
    }


    void Tree::display() {
	    printInorder(this->root);
        cout<<endl;
    }

	// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
	void printInorder(Node* root) { 
		if (root == nullptr) 
			return;
		printInorder(root->father);
		std::cout << root->name << "-" << root->relation <<"  "; 
		printInorder(root->mother); 
	}

