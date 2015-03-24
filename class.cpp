#include <string>
#include <vector>
#include "class.h" 
#include <iostream>
#include <fstream>

Requirement::Requirement(std::string l, std::string d, std::string la,Requirement * p) {
	level = l;
	description = d;
	label = la;
	empty = false;
	parent = p;
}
void Requirement::JSON(int depth,std::ofstream &outfile) {
	for(int i=0; i<depth; i++) {
		outfile << "\t";
	}
	outfile << "{\"level\":\"" << level << "\", \"description\":\"" << description << "\"";
	if(label.length() > 1) {
		outfile << ",\"label\":\"" << label <<"\"";
	}
	if(children.size() > 0) {
		outfile << ", \"children\":[" << std::endl;
		for(Requirement kid : children) {
			kid.JSON(depth+1,outfile);
		}
		for(int i=0; i<depth; i++) {
			outfile << '\t';
		}
		outfile << "]";
	}
	outfile << "}";
	if (depth != 0) {
		if (parent->children.back().description != description) {
			outfile << ",";
		}
	}
	outfile << std::endl;
}
void Requirement::Display(int depth) {
	for(int i=0; i<depth; i++) {
		std::cout << '\t';
	}
	std::cout << "level: " << level << " description:" << description << " label: " << label << std::endl;
	for (Requirement kid : children) {
		kid.Display(depth+1);
	}
}
