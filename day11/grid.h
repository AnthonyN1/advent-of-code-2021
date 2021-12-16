/*
	AnthonyN1
	Advent of Code 2021
	Day 11 - https://adventofcode.com/2021/day/11
	Grid Class
*/

#ifndef __grid_h_
#define __grid_h_

#include <fstream>
#include <utility>
#include <vector>


class Grid{
	public:
		// Constructor
		void construct(std::ifstream &stream);

		// Accessor
		unsigned int getSize() const;

		// Misc.
		unsigned int runStep();
	private:
		void getNeighbors(unsigned int r, unsigned int c, std::vector<std::pair<unsigned int, unsigned int>> &neighbors) const;
		unsigned int flash(unsigned int r, unsigned int c);

		std::vector<std::vector<unsigned int>> grid_;
		std::vector<std::vector<unsigned int>> flashed_;
};

#endif
