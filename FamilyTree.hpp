#include <iostream>
#include <string>
#include <vector>

namespace family {
	
    class Node {
        public:
            std::string name;
            std::string relation;
            family::Node *mother, *father,*child;
            int rank;

    };
	
	class Tree {
		public:
			family::Node root;
			Tree (const std::string rootName);
			Tree& addFather (const std::string sonName, const std::string fatherName);
			Tree& addMother (const std::string sonName, const std::string motherName);
			std::string find (const std::string relation2Root);
			void display ();
			Tree& remove (const std::string name) ;
			std::string relation(const std::string ancestorName);
		private:
			void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
			family::Node recursiveGetAncestorNode(const node &rootNode, const std::string ancestorName);
		
	};

}