#include <list>
class Requirement {
    public:
        bool empty;
        std::string level;
        std::string description;
        std::string label;
        Requirement const* parent;
        std::list <Requirement> children;

        Requirement(Requirement const* p);
        Requirement(std::string l, std::string d, std::string la, Requirement const* p); // unused

        void print(std::string indent = "");
        void print_json(std::ostream &os, std::string indent = "");
};
