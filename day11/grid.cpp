/*
	AnthonyN1
	Advent of Code 2021
	Day 11 - https://adventofcode.com/2021/day/11
	Grid Implementation
*/

#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "grid.h"


// Constructor
/*
	Populates the vectors using values from a stream.
	Assumes the stream outputs non-negative single-digit integers in strings.
*/
void Grid::construct(std::ifstream &stream){
	std::string temp;
	while(stream >> temp){
		// Stores each character (the single digit) in the inner vector.
		std::vector<unsigned int> innerVec;
		for(char c : temp)
			innerVec.push_back(c - '0');
		
		grid_.push_back(innerVec);

		// Creates a vector where each element is false (vector of bool is weird).
		flashed_.push_back(std::vector<unsigned int>(innerVec.size(), 0));
	}
}


// Accessor
/*
	Returns the number of elements in the Grid.
*/
unsigned int Grid::getSize() const{
	unsigned int size = 0;
	for(const std::vector<unsigned int> &row : grid_)
		size += row.size();
	
	return size;
}


// Misc.
/*
	Simulates a single step in the Grid.
*/
unsigned int Grid::runStep(){
	// Increments each element in the grid.
	for(std::vector<unsigned int> &row : grid_)
		for(unsigned int &cell : row)
			++cell;
	
	// Flashes each element greater than 9.
	unsigned int flashes = 0;
	for(unsigned int r = 0; r < grid_.size(); ++r)
		for(unsigned int c = 0; c < grid_[r].size(); ++c)
			if(grid_[r][c] > 9 && flashed_[r][c] == 0)
				flashes += flash(r, c);
	
	// Resets all flashed elements to 0.
	for(unsigned int r = 0; r < grid_.size(); ++r){
		for(unsigned int c = 0; c < grid_[r].size(); ++c){
			if(flashed_[r][c] == 1){
				grid_[r][c] = 0;
				flashed_[r][c] = 0;
			}
		}
	}

	return flashes;
}


// Private
/*
	Gets all neighboring elements, including on the diagonal.
*/
void Grid::getNeighbors(unsigned int r, unsigned int c, std::vector<std::pair<unsigned int, unsigned int>> &neighbors) const{
	for(int rMod = -1; rMod <= 1; ++rMod){
		for(int cMod = -1; cMod <= 1; ++cMod){
			if(rMod == 0 && cMod == 0) continue;

			if(((int)(r) + rMod >= 0) && (r + rMod < grid_.size()) && ((int)(c) + cMod >= 0) && (c + cMod < grid_[r + rMod].size()))
				neighbors.push_back(std::make_pair(r + rMod, c + cMod));
		}
	}
}

/*
	Flashes the element at the specified position, and potentially starts a chain-reaction with its neighbors.
*/
unsigned int Grid::flash(unsigned int r, unsigned int c){
	flashed_[r][c] = 1;
	unsigned int numFlashes = 1;

	std::vector<std::pair<unsigned int, unsigned int>> neighbors;
	getNeighbors(r, c, neighbors);

	for(const std::pair<unsigned int, unsigned int> &n : neighbors){
		++grid_[n.first][n.second];
		if(grid_[n.first][n.second] > 9 && flashed_[n.first][n.second] == 0){
			numFlashes += flash(n.first, n.second);
		}
	}

	return numFlashes;
}