/*
	AnthonyN1
	Advent of Code 2021
	Day 03 - https://adventofcode.com/2021/day/3
	Main
*/

#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <string>


/*
	Calculates the most common bit at 'pos' in every binary number in 'binNums'.
	Returns 0, 1, or 2.
	Returns 2 iff there is no most common bit.
	Assumes 'binNums' is non-empty, and 'pos' is a valid position.
*/
unsigned int calcMostCommonBit(const std::list<std::string> &binNums, unsigned int pos){
	unsigned int sum = 0;
	for(std::list<std::string>::const_iterator itr = binNums.begin(); itr != binNums.end(); ++itr)
		sum += (*itr)[pos] - '0';
	
	// '1' is the most common bit iff the sum of the bits is greater than half of the number of bits.
	if(sum > binNums.size() / 2.0){
		return 1;
	} else if(sum < binNums.size() / 2.0){
		return 0;
	} else{
		return 2;
	}
}

/*
	Removes binary numbers in 'binNums' where the bit at 'pos' does not match 'compare'.
	Assumes 'pos' is a valid position.
*/
void filter(std::list<std::string> &binNums, unsigned int pos, unsigned int compare){
	std::list<std::string>::iterator itr = binNums.begin();
	while(itr != binNums.end()){
		if((unsigned int)((*itr)[pos] - '0') != compare){
			itr = binNums.erase(itr);
		} else{
			++itr;
		}
	}
}


unsigned int part1(const std::list<std::string> &report){
	// Edge case
	if(report.size() == 0) return 0;

	unsigned int bitSize = (report.begin())->size();
	
	// Calculates the gamma rate.
	unsigned int gamma = 0;
	for(unsigned int power = 0; power < bitSize; ++power)
		if(calcMostCommonBit(report, bitSize - power - 1) == 1)
			gamma += pow(2.0, power);
	
	// The epsilon rate is mathematically equivalent to:
	unsigned int epsilon = pow(2.0, bitSize) - gamma - 1;
	
	return gamma * epsilon;
}

unsigned int part2(const std::list<std::string> &report){
	// Edge case
	if(report.size() == 0) return 0;

	// Finds the oxygen generator rating.
	std::list<std::string> oxyCopy(report);
	unsigned int pos = 0, bitCrit;
	while(oxyCopy.size() != 1){
		bitCrit = calcMostCommonBit(oxyCopy, pos);
		if(bitCrit == 2) bitCrit = 1;

		filter(oxyCopy, pos, bitCrit);

		++pos;
	}

	std::string oxyRating = *(oxyCopy.begin());

	// Finds the CO2 scrubber rating.
	std::list<std::string> co2Copy(report);
	pos = 0;
	while(co2Copy.size() != 1){
		bitCrit = calcMostCommonBit(co2Copy, pos);
		switch(bitCrit){
			case 0: bitCrit = 1; break;
			case 1: bitCrit = 0; break;
			case 2: bitCrit = 0; break;
		}

		filter(co2Copy, pos, bitCrit);

		++pos;
	}

	std::string co2Rating = *(co2Copy.begin());

	return stoi(oxyRating, 0, 2) * stoi(co2Rating, 0, 2);
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

	// Populates a list with values from the file.
	// Assumes the file contains binary numbers of the same bit-length.
	std::list<std::string> report;
	std::string binNum;
	while(file >> binNum)
		report.push_back(binNum);
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nWhat is the power consumption of the submarine?" << std::endl;
	std::cout << part1(report) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat is the life support rating of the submarine?" << std::endl;
	std::cout << part2(report) << std::endl;

	return 0;
}
