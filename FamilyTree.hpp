#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace family {
	
    class Node {
	public:
            int rank;
            std::string name;
            std::string relation;
            family::Node *mother,*father,*child;
	    Node(std::string nodeName)
	    : rank(0), name(nodeName), mother(nullptr), father(nullptr), child(nullptr)
	    {
// 	    	name = nodeName;
	    }

	    ~ Node(){
            if(mother) delete mother;
            if(father) delete father;
	    }
    };
	
	class Tree {
		public:
			family::Node* root;
			Tree (std::string rootName)
			: root(new Node(rootName)) {
                		root->relation = "me";
            		}
			Tree& addFather (std::string sonName, std::string fatherName);
			Tree& addMother (std::string sonName, std::string motherName);
			Tree& remove (std::string name) ;
			std::string find (std::string relation2Root);
			std::string relation (std::string ancestorName);
			void display ();
	};
	
}
void printInorder(family::Node* root);	
void tokenize(std::string &str, const char delim, std::vector<std::string> &out);
std::string findTemtom(int t, family::Node* temp, std::string out);
family::Node* recursiveGetAncestorNode(family::Node &rootNode, std::string ancestorName);
