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


unsigned int part1(const std::vector<std::pair<std::string, unsigned int>> &directions){
	unsigned int horizontal = 0, depth = 0;

	// Records the horizontal and vertical position of the submarine.
	// Ignores directions not in the form of "forward x", "up x", or "down x".
	for(unsigned int i = 0; i < directions.size(); ++i){
		if(directions[i].first == "forward"){
			horizontal += directions[i].second;
		} else if(directions[i].first == "up"){
			depth -= directions[i].second;
		} else if(directions[i].first == "down"){
			depth += directions[i].second;
		}
	}
	
	return horizontal * depth;
}

unsigned int part2(const std::vector<std::pair<std::string, unsigned int>> &directions){
	unsigned int horizontal = 0, aim = 0, depth = 0;

	// Records the horizontal and vertical position of the submarine.
	// Ignores directions not in the form of "forward x", "up x", or "down x".
	for(unsigned int i = 0; i < directions.size(); ++i){
		if(directions[i].first == "forward"){
			horizontal += directions[i].second;
			depth += aim * directions[i].second;
		} else if(directions[i].first == "up"){
			aim -= directions[i].second;
		} else if(directions[i].first == "down"){
			aim += directions[i].second;
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
	std::vector<std::pair<std::string, unsigned int>> directions;
	std::string str_temp;
	unsigned int int_temp;
	while(file >> str_temp >> int_temp)
		directions.push_back(std::make_pair(str_temp, int_temp));
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nWhat do you get if you multiply your final horizontal position by your final depth?" << std::endl;
	std::cout << part1(directions) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat do you get if you multiply your final horizontal position by your final depth?" << std::endl;
	std::cout << part2(directions) << std::endl;

	return 0;
}
