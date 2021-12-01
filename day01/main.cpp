/*
	AnthonyN1
	Advent of Code 2021
	Day 01 - https://adventofcode.com/2021/day/1
	Main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


unsigned int part1(const std::vector<unsigned int> &depths){
	// Edge case
	if(depths.size() < 2) return 0;

	// Counts the number of times the sequence strictly increases.
	unsigned int count = 0;
	for(unsigned int i = 1; i < depths.size(); ++i)
		if(depths[i] > depths[i - 1])
			++count;
	
	return count;
}

unsigned int part2(const std::vector<unsigned int> &depths){
	// Edge case
	if(depths.size() < 4) return 0;

	// Consdering three-element overlapping partitions,
	// counts the number of times the sequence strictly increases.
	unsigned int count = 0;
	for(unsigned int i = 3; i < depths.size(); ++i)
		if(depths[i] > depths[i - 3])
			++count;
	
	return count;
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
	// Assumes the file contains non-negative integers separated by whitespace.
	std::vector<unsigned int> depths;
	unsigned int temp;
	while(file >> temp)
		depths.push_back(temp);
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nHow many measurements are larger than the previous measurement?" << std::endl;
	std::cout << part1(depths) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nConsider sums of a three-measurement sliding window. How many sums are larger than the previous sum?" << std::endl;
	std::cout << part2(depths) << std::endl;

	return 0;
}
