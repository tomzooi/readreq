#include <list>
class Requirement {
    public:
        bool empty;
        std::string level;
        std::string description;
        std::string label;
        Requirement * parent;
        std::list <Requirement> children;
	std::list <Requirement> const * plist;
        Requirement(Requirement * p);
        
	Requirement(std::string l, std::string d, std::string la, Requirement * p); // unused

        void print(std::string indent = "");
        void print_json(std::ostream &os, std::string indent = "");
	void latex(std::ostream &os, std::string name, std::string prefix, std::string indent); 
};
