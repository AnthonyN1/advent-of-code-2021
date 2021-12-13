/*
	AnthonyN1
	Advent of Code 2021
	Day 11 - https://adventofcode.com/2021/day/11
	Main
*/

#include <fstream>
#include <iostream>
#include <string>

#include "grid.h"


unsigned int part1(Grid g){
	// Simulates 100 steps.
	unsigned int count = 0;
	for(unsigned int step = 0; step < 100; ++step)
		count += g.runStep();
	
	return count;
}

unsigned int part2(Grid &g){
	// Loops until a step is reached where all elements flash.
	unsigned int step = 1;
	while(true){
		if(g.runStep() == g.getSize())
			return step;
		
		++step;
	}

	return 0;
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

	// Populates a Grid with values from the file.
	Grid g;
	g.construct(file);

	file.close();
	

	// Part 1
	std::cout << "Part 1:\nHow many total flashes are there after 100 steps?" << std::endl;
	std::cout << part1(g) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat is the first step during which all octopuses flash?" << std::endl;
	std::cout << part2(g) << std::endl;

	return 0;
}
