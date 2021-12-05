/*
	AnthonyN1
	Advent of Code 2021
	Day 04 - https://adventofcode.com/2021/day/4
	Main
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "board.h"


/*
	Returns (by arguments) the index of the winning board, and the last drawn number.
*/
void getWinner(const std::vector<unsigned int> &draws, std::vector<Board> &boards, unsigned int &winner, unsigned int &lastDraw){
	for(unsigned int i = 0; i < draws.size(); ++i){
		for(unsigned int boardIdx = 0; boardIdx < boards.size(); ++boardIdx){
			boards[boardIdx].mark(draws[i]);
			
			if(boards[boardIdx].isComplete()){
				winner = boardIdx;
				lastDraw = draws[i];
				return;
			}
		}
	}
}

/*
*/
void getLoser(const std::vector<unsigned int> &draws, const std::vector<Board> &boards, Board &loser, unsigned int &lastDraw){
	std::list<Board> remainingBoards(boards.begin(), boards.end());

	for(unsigned int i = 0; i < draws.size(); ++i){
		std::list<Board>::iterator itr = remainingBoards.begin();
		while(itr != remainingBoards.end()){
			itr->mark(draws[i]);

			if(itr->isComplete()){
				if(remainingBoards.size() == 1){
					loser = *(remainingBoards.begin());
					lastDraw = draws[i];
					return;
				} else{
					itr = remainingBoards.erase(itr);
				}
			} else{
				++itr;
			}
		}
	}
}


unsigned int part1(const std::vector<unsigned int> &draws, std::vector<Board> &boards){
	// Edge case
	if(draws.size() < 5 || boards.size() == 0) return 0;

	// Finds the winning board.
	// Assumes the winning board exists; i.e. the draws will produce a winning board.
	unsigned int winner;
	unsigned int lastDraw;
	getWinner(draws, boards, winner, lastDraw);

	// Returns the score of the winning board.
	return boards[winner].getScore(lastDraw);
}

unsigned int part2(const std::vector<unsigned int> &draws, std::vector<Board> &boards){
	// Edge case
	if(draws.size() < 5 || boards.size() == 0) return 0;

	// Clears the marks from part 1.
	for(unsigned int i = 0; i < boards.size(); ++i)
		boards[i].clear();
	
	// Finds the losing board (the last winner).
	// Assumes all boards eventually win.
	Board loser;
	unsigned int lastDraw;
	getLoser(draws, boards, loser, lastDraw);

	// Returns the score of the losing board.
	return loser.getScore(lastDraw);
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

	// Populates a vector with values from the first line in the file.
	// Assumes the first in the line contains non-negative integers separated by commas.
	std::vector<unsigned int> draws;
	std::string line;
	file >> line;

	unsigned int pos = 0;
	unsigned int delimLoc;
	while((delimLoc = line.find(',', pos)) != (unsigned int)(-1)){
		draws.push_back(stoi(line.substr(pos, delimLoc - pos)));
		pos = delimLoc + 1;
	}
	draws.push_back(stoi(line.substr(pos)));

	// Populates a vector with the 5x5 boards in the file.
	// Assumes the number of unsigned ints in the file is a multiple of 25.
	std::vector<Board> boards;
	while(!file.eof()){
		Board temp;
		temp.construct(file);
		boards.push_back(temp);
	}
	boards.pop_back();
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nTo guarantee victory against the giant squid, figure out which board will win first. What will your final score be if you choose that board?" << std::endl;
	std::cout << part1(draws, boards) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nFigure out which board will win last. Once it wins, what would its final score be?" << std::endl;
	std::cout << part2(draws, boards) << std::endl;

	return 0;
}
