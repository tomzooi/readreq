#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include "class.h"

void parse_json(int depth, boost::property_tree::ptree const& tree, Requirement& cur)
{
    cur.label       = tree.get("label",       "");
    cur.level       = tree.get("level",       "");
    cur.description = tree.get("description", "");

    if (auto kids = tree.get_child_optional("children")) {
        for (auto& kid : *kids) {
            //std::cout << "at depth " << depth << "... " << std::flush;

            cur.children.emplace_back(&cur);

            //std::cout << "going down" << std::endl;
            parse_json(depth + 1, kid.second, cur.children.back());
        }
    }
}


int main(int argc, char *argv[]) {
	
	Requirement root(nullptr);
	std::list<Requirement> requirements;

	std::string name;
	std::string prefix;
	std::string filename;
	filename = argv[1];
	std::vector<std::string> filesplit;
	boost::split(filesplit,filename, boost::is_any_of("."));
	name = filesplit[0];
	boost::replace_all(name, "_", " ");
	prefix = filesplit[1];
	std::cout << "name: " << name << " prefix: " << prefix << std::endl << std::endl;
    try
    {
        std::ifstream ss(argv[1]);
//	std::stringstream ss;
        //ss << "{ \"root\": { \"values\": [1, 2, 3, 4, 5 ] } }";

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
	if (auto reqs = pt.get_child_optional("requirements") ) {
		for (auto& req : *reqs) {
			requirements.emplace_back(nullptr);
			parse_json(0, req.second,requirements.back());
		}
	}
       	std::cout << std::endl << std::endl;
			
	
	std::cout << std::endl << std::endl;
        for (Requirement req : requirements) {
		req.latex(std::cout, name, prefix, "#");
	}

	//root.print("; debug: ");
	return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}

