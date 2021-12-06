/*
	AnthonyN1
	Advent of Code 2021
	Day 05 - https://adventofcode.com/2021/day/5
	Main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "coordinate.h"
#include "grid.h"


unsigned int part1(const std::vector<std::pair<Coordinate, Coordinate>> &lines){
	// Adds only horizontal or vertical lines to a grid.
	Grid grid;

	for(const std::pair<Coordinate, Coordinate> &line : lines)
		if(line.first.getX() == line.second.getX() || line.first.getY() == line.second.getY())
			grid.addLine(line);
	
	// Returns the number of times at least two lines overlap.
	return grid.getNumOverlaps();
}

unsigned int part2(const std::vector<std::pair<Coordinate, Coordinate>> &lines){
	// Adds all lines to a grid.
	Grid grid;

	for(const std::pair<Coordinate, Coordinate> &line : lines)
		grid.addLine(line);
	
	// Returns the number of times at least two lines overlap.
	return grid.getNumOverlaps();
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

	// Fills a vector of pairs using coordinates in the file.
	// Assumes the file repeats the following format:
	// <int>,<int> -> <int>,<int>
	std::vector<std::pair<Coordinate, Coordinate>> lines;

	int x1, y1, x2, y2;
    char comma1, comma2;
    std::string arrow;
    while(file >> x1 >> comma1 >> y1 >> arrow >> x2 >> comma2 >> y2){
		Coordinate start(x1, y1);
		Coordinate end(x2, y2);
		lines.push_back(std::make_pair(start, end));
	}

	file.close();
	

	// Part 1
	std::cout << "Part 1:\nConsider only horizontal and vertical lines. At how many points do at least two lines overlap?" << std::endl;
	std::cout << part1(lines) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nConsider all of the lines. At how many points do at least two lines overlap?" << std::endl;
	std::cout << part2(lines) << std::endl;

	return 0;
}
