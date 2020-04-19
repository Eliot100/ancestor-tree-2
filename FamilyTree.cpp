#include "FamilyTree.hpp"

namespace family{

    family::Tree::Tree(const std::string rootName) : root(rootName) {
        this->root.relation = "me";
    }

    Tree& Tree::addFather(const std::string sonName, const std::string fatherName) {
        return *this;
    }

    Tree& Tree::addMother(const std::string sonName, const std::string motherName) {
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
        return *this;
    }

}

	// string relation (const string ancestorName){
		// node ancestorNode = recursiveGetAncestorNode(this.root, ancestorName);
		// if(ancestorNode == NULL)
			// return "unrelated";
		// return ancestorNode.name;
	// }
    //private:
    //node recursiveGetAncestorNode(const node &rootNode, string ancestorName){
    //	if(rootNode.name == ancestorName)
    //		return rootNode.relation;
    //	node& ancestorNode;
    //	if(rootNode->father != NULL){
    //		ancestorNode = recursiveGetAncestorNode(rootNode->father, ancestorName);
    //		if(ancestorNode != NULL)
    //			return &ancestorNode;
    //	}
    //	if(rootNode->mother != NULL){
    //		ancestorNode = recursiveGetAncestorNode(rootNode->mother, ancestorName);
    //		if(ancestorNode != NULL)
    //			return &ancestorNode;
    //	}
    //}

