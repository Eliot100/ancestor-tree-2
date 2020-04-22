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
            family::Node *mother, *father, *child;
	    Node(const std::string nodeName);
    };
	
	class Tree {
		public:
			family::Node root;
			Tree (const std::string rootName);
			Tree& addFather (const std::string sonName, const std::string fatherName);
			Tree& addMother (const std::string sonName, const std::string motherName);
			Tree& remove (const std::string name) ;
			std::string find (const std::string relation2Root);
			std::string relation (const std::string ancestorName);
			void display ();
	};
	
	
}
	void printInorder(Node* root);	
	void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
	std::string findTemtom(int t, Node* temp, std::string out);
	family::Node* recursiveGetAncestorNode(Node &rootNode, const std::string ancestorName);
