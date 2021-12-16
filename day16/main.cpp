/*
	AnthonyN1
	Advent of Code 2021
	Day 16 - https://adventofcode.com/2021/day/16
	Main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "packet.h"


unsigned int part1(const Packet &p){
	// Sums the versions of the outer packet and its sub-packets.
	return p.sumVersions();
}

unsigned long long part2(const Packet &p){
	// Gets the value represented by the expression in the packet.
	return p.getValue();
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

	// Populates a vector with the value from the file.
	// Assumes the file contains a hexadecimal number.
	std::vector<unsigned int> binNum;

	std::string line;
	file >> line;

	// Converts the hexadecimal number to binary.
	for(char c : line){
		// Converts the character to a decimal number.
		unsigned int num;
		if(c >= '0' && c <= '9') num = c - '0';
		else num = c - 'A' + 10;

		for(unsigned int place = 8; place >= 1; place /= 2){
			if(num / place == 1){
				binNum.push_back(1);
				num -= place;
			} else{
				binNum.push_back(0);
			}
		}
	}
	
	file.close();


	// Assumes the binary number is a valid packet.
	Packet p(binNum);
	

	// Part 1
	std::cout << "Part 1:\nDecode the structure of your hexadecimal-encoded BITS transmission; what do you get if you add up the version numbers in all packets?" << std::endl;
	std::cout << part1(p) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat do you get if you evaluate the expression represented by your hexadecimal-encoded BITS transmission?" << std::endl;
	std::cout << part2(p) << std::endl;

	return 0;
}
