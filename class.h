#include <vector>
class Requirement {
	public:
		bool empty;
		std::string level;
		std::string description;
		std::string label;
		std::vector <Requirement> children;
		Requirement * parent;
		Requirement(std::string l, std::string d, std::string la, Requirement * p);
		void Display(int depth);
		void JSON(int depth, std::ofstream &outfile);
};
