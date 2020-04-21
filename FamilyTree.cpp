#include "FamilyTree.hpp"

namespace family{
	
    family::Node::Node(const std::string nodeName) : name(nodeName) {}

    family::Tree::Tree(const std::string rootName) : root(rootName) {
        this->root.relation = "me";
        this->root.rank=0; 
    }

    Tree& Tree::addFather(const std::string sonName, const std::string fatherName) {
	    Node sonNode = recursiveGetAncestorNode(this->root , sonName);
		Node* father = new Node(fatherName);
        father->child = &sonNode;
        father->rank = sonNode.rank+1;
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
        sonNode.father = father;			
        return *this;
    }

    Tree& Tree::addMother(const std::string sonName, const std::string motherName) {
        Node sonNode = recursiveGetAncestorNode(this->root , sonName);
        Node* mother = new Node(motherName);
        mother->child = &sonNode;
        mother->rank = sonNode.rank+1;
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
        sonNode.mother = mother;
        return *this;
    }

    void Tree::display() {
		std::cout << this->root.name ;
		
    }

    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out){
        size_t start;
        size_t end = 0;
        while ((start = str.find_first_not_of(delim, end)) != std::string::npos){
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
    }

    std::string Tree::find(const std::string relation2Root) {
        int L = relation2Root.length(), i = 0;
        Node *temp = this->root;
        if (L > 11) {
            const char delim = '-';
            std::vector <std::string> out;
            tokenize(relation2Root, delim, out);
            int r = out.length();
            if (out[r - 1].compare("grandmother")) {
                for (i; i < r; i++) {
                    temp = temp->mother;
                }
                return temp->name;
            } else {
                if (out[r - 1].compare("grandfather")) {
                    for (i; i < r; i++) {
                        temp = temp->father;
                    }
                    return temp->name;
                }
                else  return "unrelated";
            }
        } else {
            if (relation2Root.compare("mother"))
                return this->root->mother->name;
            else if (relation2Root.compare("father"))
                return this->root->father->name;
            else if (relation2Root.compare("grandmother"))
                return this->root->mother->mother->name;
            else if (relation2Root.compare("grandfather"))
                return this->root->father->father->name;
            else
                return "unrelated";

        }
    }

    std::string Tree::relation(const std::string ancestorName) {
		Node ancestorNode = recursiveGetAncestorNode(this->root, ancestorName);
        if(ancestorNode == NULL)
			return "unrelated";
		return ancestorNode.relation;
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
	
    Node& recursiveGetAncestorNode(const Node &rootNode, string ancestorName){
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
