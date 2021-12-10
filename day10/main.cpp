/*
	AnthonyN1
	Advent of Code 2021
	Day 10 - https://adventofcode.com/2021/day/10
	Main
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

const std::map<char, unsigned int> CORR_POINTS{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
const std::map<char, unsigned int> INCOM_POINTS{{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
const std::map<char, char> MATCHING_PARENS{{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};


/*
	Returns '-' (false) iff the string is missing a closing bracket.
	Assumes the string only consists of the following characters: "()[]{}<>".
	Assumes strings are only incomplete at their end.
*/
char isCorrupted(const std::string &paren){
	std::stack<char> matches;
	for(char ch : paren){
		if(MATCHING_PARENS.find(ch) != MATCHING_PARENS.cend()) matches.push(ch);
		else if(MATCHING_PARENS.at(matches.top()) == ch) matches.pop();
		else return ch;
	}

	return '-';
}

/*
	Returns an empty string (false) iff the string has matching open and closing brackets.
	Assumes the string is not corrupted.
*/
std::string isIncomplete(const std::string &paren){
	std::stack<char> matches;
	for(char ch : paren){
		if(MATCHING_PARENS.find(ch) != MATCHING_PARENS.cend()) matches.push(ch);
		else matches.pop();
	}

	std::string missing = "";
	while(!matches.empty()){
		missing += MATCHING_PARENS.at(matches.top());
		matches.pop();
	}

	return missing;
}


unsigned int part1(std::vector<std::string> &parens){
	// Finds the corrupted lines, and sums their scores.
	unsigned int sum = 0;
	for(const std::string &paren : parens){
		char corruption = isCorrupted(paren);
		if(corruption != '-') sum += CORR_POINTS.at(corruption);
	}
	
	return sum;
}

unsigned long part2(const std::vector<std::string> &parens){
	// Finds the incomplete lines, and takes the middle of their scores.
	std::vector<unsigned long> scores;
	for(const std::string &paren : parens){
		// Discards corrupted lines.
		char corruption = isCorrupted(paren);
		if(corruption != '-') continue;

		// Discards complete lines.
		std::string incomplete = isIncomplete(paren);
		if(incomplete == "") continue;

		// Calculates the score of the line.
		unsigned long score = 0;
		for(char ch : incomplete){
			score *= 5;
			score += INCOM_POINTS.at(ch);
		}
		scores.push_back(score);
	}

	// Assumes there will always be an odd number of scores.
	std::sort(scores.begin(), scores.end());
	return scores[scores.size() / 2];
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
	// Assumes the lines in the file are uninterrupted strings.
	std::vector<std::string> parens;
	std::string temp;
	while(file >> temp)
		parens.push_back(temp);
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nWhat is the total syntax error score for those errors?" << std::endl;
	std::cout << part1(parens) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat is the middle score?" << std::endl;
	std::cout << part2(parens) << std::endl;

	return 0;
}
