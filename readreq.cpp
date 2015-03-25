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

void parse_req(unsigned int cur_depth, std::ifstream &f, std::list<Requirement> &reqlist,unsigned int linenr=0) {
	std::string line;
	unsigned int count = 0;
	unsigned int depth = 0;
	Requirement * cur(nullptr);
	boost::regex re("\\t+|\\s{2,}"); //regex split parameter (one or more tabs or 2 or more spaces)

	std::list<Requirement>* lptr(&reqlist);
	while (std::getline(f, line))	{
		linenr++;
	    //	std::cout << "(" << linenr << "): " << line; 
		depth = line.find_first_not_of(" 	"); //find first none space or tab character
		
		
		boost::sregex_token_iterator i(line.begin()+depth, line.end(), re, -1); //split line by tabs and spaces
		boost::sregex_token_iterator j;
		count = 0; //reset count
		if (depth == cur_depth) {
			lptr->emplace_back(lptr->back().parent);
			cur = &lptr->back();
		}
		else if (depth > cur_depth) { //go deeper
			cur_depth = depth;
			lptr = &lptr->back().children;
			lptr->emplace_back(cur);
			cur = &lptr->back();
		}
		else if (depth < cur_depth) { //go down
			//lptr = cur->parent;
			while (cur_depth > depth) { 
				cur_depth--;
				std::cout << "deeper : " << cur_depth << std::endl << std::flush;
				lptr = &(lptr->back().parent->parent->children);
			}
			if(cur_depth != 0) {
				lptr->emplace_back(lptr->back().parent);
				cur = &lptr->back();
			}
			else {
				reqlist.emplace_back(nullptr);
				cur = &reqlist.back();
			}
		}
		while(i != j) { //for all splitted parts
			switch(count) {
				case 0:
					cur->level  =*i++;
					//std::cout << "lvl: " << cur->level << " ";
					break;
				case 1:
					cur->description = *i++;
					//std::cout << "dsc: " << cur.description << std::endl;
					break;
				case 2:
					cur->label = *i++;
					break;
				default:
					*i++;
					break;
			}
			count++;
		}
		if (count < 2) { //too less arguments
			std::cout << "ERROR(" << linenr << "): nead at least two parts for an requirement (level and description), less than two found, halting." << std::endl;
			break;
		}
		if (count > 3) { //too much arguments
			std::cout << "WARNING(" << linenr << "): More then three arguments found, ignoring fourth or more argument" << std::endl;
		}
	}
}
int main(int argc, char *argv[]) {
//	class Requirement req("will",  "do good work", "good");
	if ( argc != 3 ) // argc should be 2 for correct execution
	    // We print argv[0] assuming it is the program name
	    std::cout<<"usage: "<< argv[0] <<" <filename input> <filename output>\n";
	 else {
		std::ifstream file(argv[1]); //try to open file
		if(!file.is_open()) { //if we can't
			std::cout << "Could not open file" ;
		}
		else { //sucesfully opened file
			std::list<Requirement> requirements;
			parse_req(0,file,requirements);

			std::ofstream outfile(argv[2]); //try to open file
			outfile << "{ \"requirements\":[";
			for (Requirement req : requirements) {
				
				req.print();
				req.print_json(outfile);
				if (requirements.back().description != req.description) {
					outfile << ",";
				}
			}
			outfile << "]}";
			std::cout << "success!" << std::endl;
			}

		}
	 
	return 0;
}

