/*
	AnthonyN1
	Advent of Code 2021
	Day 06 - https://adventofcode.com/2021/day/6
	Main
*/

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>


/*
	Runs a simulation of lanternfish spawning for a specified number of days.
*/
void runDays(std::vector<unsigned long long> &numFishAtDay, unsigned int days){
	for(unsigned int i = 0; i < days; ++i){
		unsigned long long numAtZero = numFishAtDay[0];
		for(unsigned int days = 0; days < numFishAtDay.size() - 1; ++days){
			numFishAtDay[days] = numFishAtDay[days + 1];
		}

		numFishAtDay[8] = numAtZero;
		numFishAtDay[6] += numAtZero;
	}
}


unsigned long long part1(std::vector<unsigned long long> numFishAtDay){
	runDays(numFishAtDay, 80);
	return std::accumulate(numFishAtDay.begin(), numFishAtDay.end(), (unsigned long long)(0));
}

unsigned long long part2(std::vector<unsigned long long> numFishAtDay){
	runDays(numFishAtDay, 256);
	return std::accumulate(numFishAtDay.begin(), numFishAtDay.end(), (unsigned long long)(0));
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

	// Populates a vector with numbers from the file.
	// Assumes the file is one line long, with that line containing unsigned ints separated by a comma.
	std::string line;
	std::getline(file, line);
	
	std::vector<unsigned long long> numFishAtDay(9, 0);
	unsigned int pos = 0;
	unsigned int delimLoc;
	while((delimLoc = line.find(',', pos)) != (unsigned int)(-1)){
		numFishAtDay[std::stoi(line.substr(pos, delimLoc - pos))]++;
		pos = delimLoc + 1;
	}
	numFishAtDay[std::stoi(line.substr(pos))]++;
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nHow many lanternfish would there be after 80 days?" << std::endl;
	std::cout << part1(numFishAtDay) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nHow many lanternfish would there be after 256 days?" << std::endl;
	std::cout << part2(numFishAtDay) << std::endl;

	return 0;
}
