/*
	AnthonyN1
	Advent of Code 2021
	Day 13 - https://adventofcode.com/2021/day/13
	Main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "paper.h"

struct Instruction{
	Instruction(char axis, unsigned int pos): axis_(axis), pos_(pos) {}
	char axis_;
	unsigned int pos_;
};


unsigned int part1(Paper &p, const std::vector<Instruction> &instrs){
	// Counts the number of dots after the first instruction.
	// Assumes there's one or more instructions.
	if(instrs[0].axis_ == 'x'){
		p.foldX(instrs[0].pos_);
	} else{
		p.foldY(instrs[0].pos_);
	}
	
	return p.getDots();
}

void part2(Paper &p, const std::vector<Instruction> &instrs){
	// Finishes the vector of instructions, and prints the paper to reveal the code.
	for(unsigned int i = 1; i < instrs.size(); ++i){
		if(instrs[i].axis_ == 'x'){
			p.foldX(instrs[i].pos_);
		} else{
			p.foldY(instrs[i].pos_);
		}
	}
}


int main(int argc, char* argv[]){
	// Error checking: correct number of arguments.
	if(argc != 2){
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		std::cerr << "       Usage: ./main.exe <input_file>\n";
		std::cerr << "       Exiting..." << std::endl;
		return -1;
	}

	// Initializes the input stream.
	// Error checking: successfully opened the file.
	std::ifstream file(argv[1]);
	if(!file.is_open()){
		std::cerr << "ERROR: Unable to open input file.\n";
		std::cerr << "       Exiting..." << std::endl;
		return -1;
	}

	// Populates a Paper object with values from the file.
	// Assumes the file two sections:
	// The first section contains lines of two unsigned ints, separated by ','.
	// The second section contains lines of the form: "fold along <y/x>=<unsigned int>".
	Paper p;
	std::vector<Instruction> instrs;

	std::string line;
	while(std::getline(file, line)){
		// Assumes the two sections are partitioned by a blank line.
		if(line == ""){
			continue;
		} else if(line[0] == 'f'){
			unsigned int delimLoc = line.find('=');
			char axis = line[delimLoc - 1];
			unsigned int pos = std::stoi(line.substr(delimLoc + 1));

			instrs.push_back(Instruction(axis, pos));
		} else{
			unsigned int delimLoc = line.find(',');
			unsigned int x = std::stoi(line.substr(0, delimLoc));
			unsigned int y = std::stoi(line.substr(delimLoc + 1));

			p.addDot(x, y);
		}
	}
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nHow many dots are visible after completing just the first fold instruction on your transparent paper?" << std::endl;
	std::cout << part1(p, instrs) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat code do you use to activate the infrared thermal imaging camera system?" << std::endl;
	part2(p, instrs);
	p.print();

	return 0;
}
