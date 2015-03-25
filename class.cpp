#include <string>
#include <list>
#include "class.h" 
#include <iostream>
#include <fstream>

Requirement::Requirement(Requirement * p) 
    : empty(false), parent(p)
{
}

Requirement::Requirement(std::string l, std::string d, std::string la,Requirement * p) // unused
    : empty(false), 
      level(std::move(l)), description(std::move(d)), label(std::move(la)), parent(p)
{
}

void Requirement::print_json(std::ostream &os, std::string indent) {
    os  << "{";
    indent += '\t';

    os
         << "\n" << indent << "\"level\":\""       << level       << "\", "
         << "\n" << indent << "\"description\":\"" << description << "\"";

    if(label.length() > 1) {
        os << ",\n" << indent << "\"label\":\"" << label <<"\"";
    }

    if (!children.empty()) {
        os << ", \"children\":[\n";

        bool first = true;
        for(auto& child : children) {
            if (!first)
                os << ',';

            first=false;

            os << "\n" << indent;
            child.print_json(os, indent);
        }
        os << "]";
    }

    indent.resize(indent.size() - 1);
    os << "\n" << indent << "}";
}

void Requirement::print(std::string indent) {
    std::cout << indent << "level: " << level << " description:" << description << " label: " << label << std::endl;
    for (Requirement kid : children)
        kid.print(indent + '\t');
}
void Requirement::latex(std::ostream &os, std::string name, std::string prefix, std::string indent) {
    os << indent << " " << name << " " << level << " " << description << std::endl;
    for (Requirement kid : children)
        kid.latex(os,name,prefix,indent + '#');
}
