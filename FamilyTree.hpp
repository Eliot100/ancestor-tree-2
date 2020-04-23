#include <iostream>
#include <string>
using namespace std;

namespace family {

    class Node {
    public:
        int rank;
        std::string name;
        std::string relation;
        family::Node *mother, *father, *child;
        Node(std::string nodeName)
                : rank(0), name(nodeName), mother(nullptr), father(nullptr), child(nullptr)
        {}

        ~ Node(){
            if(mother != nullptr)
                delete mother;
            if(father != nullptr)
                delete father;
        }
    };

    class Tree {
    public:
        family::Node* root;
        Tree (std::string rootName)
                : root(new Node(rootName)) {
            root->relation = "me";
        }

        ~ Tree(){
            delete root;
        }

        Tree& addFather (std::string sonName, std::string fatherName);
        Tree& addMother (std::string sonName, std::string motherName);
        Tree& remove (std::string name);
        std::string relation (std::string ancestorName);
        std::string find (std::string relation2Root);
        void display ();
    };
}

family::Node* recursiveGetAncestorNode(family::Node* rootNode, std::string ancestorName);
family::Node* recursiveGetAncestorNodeByRelation(family::Node* rootNode, std::string ancestorRelation);
void printInorder(family::Node* root);
void remove2 (family::Node* parent);
