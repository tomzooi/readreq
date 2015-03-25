#include <fstream>
#include <iostream>
#include "class.h" 
#include <vector>
#include <string>
//#include <regex>
#include <boost/regex.hpp>
#include <iterator>
#include <algorithm>
#include <math.h>

//how many spaces are interpreted as one tab or level
#define SPACES 8 
#define LINEBUFSIZE 500 
int main(int argc, char *argv[]) {
//	class Requirement req("will",  "do good work", "good");
	//std::cout << "The system " << req.level << " " << req.description << std::endl;
	if ( argc != 3 ) // argc should be 2 for correct execution
	    // We print argv[0] assuming it is the program name
	    std::cout<<"usage: "<< argv[0] <<" <filename input> <filename output>\n";
	 else {
		std::ifstream file(argv[1]); //try to open file
		if(!file.is_open()) { //if we can't
			std::cout << "Could not open file" ;
		}
		else { //sucesfully opened file
			char line[LINEBUFSIZE]; //buffer for reading file
			std::string linestr; //string for regex and string stuff
		 	boost::regex re("\\t+|\\s{2,}"); //regex split parameter (one or more tabs or 2 or more spaces)
			unsigned int count;
			unsigned int depth;
			unsigned int current_depth = 0;
			bool start = true;

			std::string req_level;
			std::string req_desc;
			std::string req_label;
			
			Requirement cur_requirement(nullptr);
			std::list <Requirement> requirements;

			size_t spaces, tabs;
			unsigned int linenr = 0; 
			
			while(file.getline(line,LINEBUFSIZE)) { //for every line in the file
				linenr++;
				linestr = line; //store the line in the string
				count = 0;
				while(line[count] == '\t' || line[count] == ' ') {//count tabs or spaces for depth
					count++;
				}
				spaces  = std::count(linestr.begin(), linestr.begin()+count, ' ');	
				tabs  = std::count(linestr.begin(), linestr.begin()+count, '\t');
				depth = tabs + floor(spaces/SPACES);
				
				//Split string into parts and count them
				boost::sregex_token_iterator i(linestr.begin()+count, linestr.end(), re, -1);
				boost::sregex_token_iterator j;
				count = 0; //reset count
				req_label = ""; //reset label
	     			while(i != j) {
					switch(count) {
						case 0:
							cur_requirement.label  =*i++;
							break;
						case 1:
							cur_requirement.description = *i++;
							break;
						case 2:
							cur_requirement.label = *i++;
							break;
						default:
							*i++;
							break;
					}
					count++;
					//std::cout << *i++ << " | " ;
			      	}
				if (count < 2) {
					std::cout << "ERROR(" << linenr << "): nead at least two parts for an requirement (level and description), less than two found, halting." << std::endl;
					break;
				}
				if (count > 3) {
					std::cout << "WARNING(" << linenr << "): More then three arguments found, ignoring fourth or more argument" << std::endl;
				}
				
				if (depth == 0) {
					//requirements.emplace_back(req_level, req_desc, req_label,cur_requirement);
					requirements.emplace_back(&cur_requirement);
					cur_requirement = &requirements.back();
				}
				else if (depth != 0 && start) {
					std::cout << "ERROR: First element has to be of depth zero!" << std::endl;
				}
				else {
					if (depth == 1) {
						requirements.back().children.emplace_back(&cur_requirement);
						cur_requirement = &requirements.back().children.back(); 
						current_depth = 1;
					}
					else if (current_depth == depth) {
						cur_requirement.parent->children.emplace_back(&cur_requirement);
						cur_requirement = &cur_requirement.back().parent->children.back();
					}
					else if(current_depth == (depth-1)) { //depth is one deeper than current depth
						cur_requirement.children.emplace_back(&cur_requirement.children.back());
						cur_requirement = &cur_requirement.children.back();
						current_depth = depth;
					}
					else if (current_depth < (depth-1)) { //depth is more than one deeper than current depth
						while(current_depth != (depth-1)) { //until depth is one deeper than current depth
							cur_requirement.children.emplace_back("empty", "empty", "empty",&cur_requirement); //add empty element
							cur_requirement = &cur_requirement.children.back();
							current_depth++;
						}
						cur_requirement.children.emplace_back(&cur_requirement);
						cur_requirement = &cur_requirement.children.back();
						current_depth = depth;
					}
					else if(current_depth > depth) { //we are to deep, go up!
						while (current_depth != depth) {
							cur_requirement = cur_requirement.parent;
							current_depth--;
						}
						//cur_requirement.parent->children.emplace_back(&cur_requirement.children.back());
					}


				} 
			start = false;
			}

			std::ofstream outfile(argv[2]); //try to open file
			for (Requirement req : requirements) {
				req.print();
			}
			if(argv[3] == "latex") {
				std::cout << "parsing to latex..." << std::endl;
				for (Requirement req : requirements) {
					req.print_json(outfile);
				}
				

			}
			else {
				std:: cout << "parsing to screen..." << std::endl;
				for (Requirement req : requirements) {
					req.print_json(outfile);
				}
				std::cout << "success!" << std::endl;
			}

		}
	 }
	return 0;
}

