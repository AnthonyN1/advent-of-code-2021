/*
	AnthonyN1
	Advent of Code 2021
	Day 07 - https://adventofcode.com/2021/day/7
	Main
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

typedef std::map<int, unsigned int> crab_count;


unsigned int part1(const crab_count &crabs, int min, int max){
	unsigned int lowestDelta = (unsigned int)(-1);
	for(int pos = min; pos <= max; ++pos){
		unsigned int delta = 0;
		for(crab_count::const_iterator itr = crabs.cbegin(); itr != crabs.cend(); ++itr){
			delta += itr->second * std::abs(pos - itr->first);
		}

		if(delta < lowestDelta) lowestDelta = delta;
	}

	return lowestDelta;
}

unsigned int part2(const crab_count &crabs, int min, int max){
	unsigned int lowestDelta = (unsigned int)(-1);
	for(int pos = min; pos <= max; ++pos){
		unsigned int delta = 0;
		for(crab_count::const_iterator itr = crabs.cbegin(); itr != crabs.cend(); ++itr){
			unsigned int dist = std::abs(pos - itr->first);
			delta += itr->second * (dist * (dist + 1) / 2);
		}

		if(delta < lowestDelta) lowestDelta = delta;
	}

	return lowestDelta;
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

	// Populates a map with values from the file.
	// Assumes the file contains integers separated by commas.
	crab_count crabs;
	std::string line;
	file >> line;
	
	unsigned int pos = 0;
	unsigned int delimLoc;
	while((delimLoc = line.find(',', pos)) != (unsigned int)(-1)){
		crabs[std::stoi(line.substr(pos, delimLoc - pos))]++;
		pos = delimLoc + 1;
	}
	crabs[std::stoi(line.substr(pos))]++;
	
	file.close();

	int min = (crabs.cbegin())->first;
	int max = (crabs.cend())->first;
	

	// Part 1
	std::cout << "Part 1:\nHow much fuel must they spend to align to that position?" << std::endl;
	std::cout << part1(crabs, min, max) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nHow much fuel must they spend to align to that position?" << std::endl;
	std::cout << part2(crabs, min, max) << std::endl;

	return 0;
}
