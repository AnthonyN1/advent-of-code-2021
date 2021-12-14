/*
	AnthonyN1
	Advent of Code 2021
	Day 01 - https://adventofcode.com/2021/day/1
	Main
*/

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>

typedef std::pair<char, char> poly_pair;


/*
	Returns the maximum value in a map.
*/
unsigned long long maxValue(const std::map<char, unsigned long long> &map){
	unsigned long long max = 0;
	for(std::map<char, unsigned long long>::const_iterator itr = map.cbegin(); itr != map.cend(); ++itr)
		if(itr->second > max)
			max = itr->second;

	return max;
}

/*
	Returns the minimum value in a map.
*/
unsigned long long minValue(const std::map<char, unsigned long long> &map){
	unsigned long long min = std::numeric_limits<unsigned long long>::max();
	for(std::map<char, unsigned long long>::const_iterator itr = map.cbegin(); itr != map.cend(); ++itr)
		if(itr->second < min)
			min = itr->second;

	return min;
}

/*
	Inserts elements in the list according to the insertion rules.
*/
void runStep(std::map<poly_pair, unsigned long long> &polyTemplate, std::map<char, unsigned long long> &charCount, const std::map<poly_pair, char> &rules){
	std::map<poly_pair, unsigned long long> replacement;

	for(std::map<poly_pair, unsigned long long>::iterator itr = polyTemplate.begin(); itr != polyTemplate.end(); ++itr){
		std::map<poly_pair, char>::const_iterator rulesItr = rules.find(itr->first);
		if(rulesItr == rules.end()) continue;

		char insertElement = rulesItr->second;
		replacement[poly_pair((itr->first).first, insertElement)] += itr->second;
		replacement[poly_pair(insertElement, (itr->first).second)] += itr->second;

		charCount[insertElement] += itr->second;
	}

	polyTemplate = replacement;
}


unsigned long long part1(std::map<poly_pair, unsigned long long> &polyTemplate, std::map<char, unsigned long long> &charCount, const std::map<poly_pair, char> &rules){
	// Simulates 10 insertion steps.
	for(unsigned int i = 0; i < 10; ++i)
		runStep(polyTemplate, charCount, rules);


	return maxValue(charCount) - minValue(charCount);
}

unsigned long long part2(std::map<poly_pair, unsigned long long> &polyTemplate, std::map<char, unsigned long long> &charCount, std::map<poly_pair, char> &rules){
	// Simulates 30 more insertion steps.
	for(unsigned int i = 0; i < 30; ++i)
		runStep(polyTemplate, charCount, rules);


	return maxValue(charCount) - minValue(charCount);
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
	// Assumes the first line in the file is a string.
	std::map<poly_pair, unsigned long long> polyTemplate;
	std::map<char, unsigned long long> charCount;

	std::string temp;
	file >> temp;

	++charCount[temp[0]];
	for(unsigned int i = 1; i < temp.size(); ++i){
		++polyTemplate[poly_pair(temp[i - 1], temp[i])];
		++charCount[temp[i]];
	}
	
	// Assumes the line is followed by a blank line, then lines of the following form:
	// <two alphabetic characters> -> <character>
	std::map<poly_pair, char> rules;
	std::string first, delim, second;
	while(file >> first >> delim >> second){
		rules[poly_pair(first[0], first[1])] = second[0];
	}
	
	file.close();

	std::cout << std::numeric_limits<unsigned long long>::max() << std::endl;
	

	// Part 1
	std::cout << "Part 1:\nWhat do you get if you take the quantity of the most common element and subtract the quantity of the least common element?" << std::endl;
	std::cout << part1(polyTemplate, charCount, rules) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat do you get if you take the quantity of the most common element and subtract the quantity of the least common element?" << std::endl;
	std::cout << part2(polyTemplate, charCount, rules) << std::endl;

	return 0;
}
