/*
	AnthonyN1
	Advent of Code 2021
	Day 02 - https://adventofcode.com/2021/day/2
	Main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


struct Instruction{
	Instruction(const std::string &direction, unsigned int magnitude): direction_(direction), magnitude_(magnitude) {}
	std::string direction_;
	unsigned int magnitude_;
};


unsigned int part1(const std::vector<Instruction> &instructions){
	unsigned int horizontal = 0, depth = 0;

	// Records the horizontal and vertical position of the submarine.
	// Assumes directions are in the form of "forward x", "up x", or "down x".
	for(const Instruction &inst : instructions){
		if(inst.direction_ == "forward") horizontal += inst.magnitude_;
		else if(inst.direction_ == "up") depth -= inst.magnitude_;
		else if(inst.direction_ == "down") depth += inst.magnitude_;
	}
	
	return horizontal * depth;
}

unsigned int part2(const std::vector<Instruction> &instructions){
	unsigned int horizontal = 0, aim = 0, depth = 0;

	// Records the horizontal and vertical position of the submarine.
	// Assumes directions are in the form of "forward x", "up x", or "down x".
	for(const Instruction &inst : instructions){
		if(inst.direction_ == "forward"){
			horizontal += inst.magnitude_;
			depth += aim * inst.magnitude_;
		} else if(inst.direction_ == "up"){
			aim -= inst.magnitude_;
		} else if(inst.direction_ == "down"){
			aim += inst.magnitude_;
		}
	}
	
	return horizontal * depth;
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

	// Populates a vector with values from the file.
	// Assumes the file contains pairs of strings and non-negative integers separated by whitespace.
	std::vector<Instruction> instructions;
	std::string strTemp;
	unsigned int intTemp;
	while(file >> strTemp >> intTemp)
		instructions.push_back(Instruction(strTemp, intTemp));
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nWhat do you get if you multiply your final horizontal position by your final depth?" << std::endl;
	std::cout << part1(instructions) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat do you get if you multiply your final horizontal position by your final depth?" << std::endl;
	std::cout << part2(instructions) << std::endl;

	return 0;
}
