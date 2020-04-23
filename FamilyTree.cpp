#include "FamilyTree.hpp"
#include <exception>
using namespace family;

    Tree& Tree::addFather(std::string sonName,std::string fatherName) {
	Node* sonNode = recursiveGetAncestorNode(this->root , sonName);
	if ((sonNode->name!=sonName)) {
		throw runtime_error(sonNode->name);
	}
	if ((sonNode->father!=(nullptr))) {
        	throw runtime_error("lala");
    	}

	Node* father = new Node(fatherName);
        father->child = sonNode;
        father->rank = (sonNode->rank)+1;
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

    void Tree::display() {
	    printInorder(this->root);
        cout<<endl;
    }

    void tokenize(std::string &str, const char delim, std::vector<std::string> &out){
        size_t start;
        size_t end = 0;
        while ((start = str.find_first_not_of(delim, end)) != std::string::npos){
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
    }

    std::string findTemtom(int t, Node* temp, std::string out) {
        if (t > 0) {
            if (temp->mother != nullptr)
                return findTemtom(t - 1, temp->mother, out);
            if (temp->father != nullptr)
                return findTemtom(t - 1, temp->father, out);
        } else {
            if (out =="grandmother" && (temp->mother != nullptr)) {
                return temp->mother->name;
            } else if (out=="grandfather" && (temp->father != nullptr)) {
                return temp->father->name;
            }
        }
        return "NULL";
    }
    std::string Tree::find( std::string relation2Root) {
	   Node* ancestorNode = nullptr;
    	   ancestorNode = recursiveGetAncestorNodeByRelation(this->root, relation2Root);
	   if(ancestorNode == nullptr)
		   throw std::runtime_error("error");
	   return *ancestorNode->name;
		   
//         int L = relation2Root.size();
//         int i = 0;
//         Node temp = *this->root;
//         if (L > 11) {
	
//             const char delim = '-';
//             std::vector <std::string> out;
// 	    return 
//             //tokenize(relation2Root, delim, out);
//             //int r = out.size();
//             //std::string temtom = findTemtom(r, &temp, out[r - 1]);
//             //if (temtom == "NULL")
//             //    throw (std::runtime_error("error"));
//             //return temtom;
//         } else {
//             if (relation2Root == "mother")
//                 return this->root->mother->name;
//             else if (relation2Root == "father")
//                 return this->root->father->name;
//             else if (relation2Root == "grandmother")
//                 return this->root->mother->mother->name;
//             else if (relation2Root == "grandfather")
//                 return this->root->father->father->name;
//             else throw (std::runtime_error("error"));
//         }
    }

    std::string Tree::relation( std::string ancestorName) {
		Node* ancestorNode = recursiveGetAncestorNode(this->root, ancestorName);
        if(ancestorNode == nullptr)
			return "unrelated";
		return ancestorNode->relation;
    }

    Tree& Tree::remove( std::string name) {
        Node* removeNode = recursiveGetAncestorNode(this->root , name);
        if (removeNode->rank == 0)
            throw(std::runtime_error("error"));
        remove(removeNode->father->name);
        remove(removeNode->mother->name);
        if(removeNode->child->father->name == name){
            removeNode->child->father = NULL;
        }
        else{
            removeNode->child->mother = NULL;
        }
        delete removeNode;
        return *this;
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

	// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
	void printInorder(Node* root) { 
		if (root == NULL) 
			return;
		printInorder(root->father);
		std::cout << root->name << "-" << root->relation <<" "; 
		printInorder(root->mother); 
	}

