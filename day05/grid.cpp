/*
	AnthonyN1
	Advent of Code 2021
	Day 05 - https://adventofcode.com/2021/day/5
	Grid Implementation
*/

#include <unordered_map>
#include <utility>

#include "grid.h"


// Coordinate Non-member
/*
	Returns true iff each member variable is equal.
*/
bool operator==(const Coordinate &c1, const Coordinate &c2){
	return c1.x_ == c2.x_ && c1.y_ == c2.y_;
}


// Modifier
/*
	Adds a line (using integer coordinates) to the hash map.
	Checks if the added line collides with existing lines.
*/
void Grid::addLine(const std::pair<Coordinate, Coordinate> &line){
	Coordinate c1 = line.first;
	Coordinate c2 = line.second;

	int currX = c1.x_, currY = c1.y_;
	while(currX != c2.x_ || currY != c2.y_){
		Coordinate newCoord(currX, currY);
		grid_[newCoord]++;

		if(grid_[newCoord] == 2) ++numOverlaps_;

		// Advances towards the second coordinate.
		if(currX != c2.x_) currX += (c1.x_ < c2.x_) ? 1 : -1;
		if(currY != c2.y_) currY += (c1.y_ < c2.y_) ? 1 : -1;
	}

	// Repeats for the second coordinate (loop condition).
	Coordinate newCoord(currX, currY);
	grid_[newCoord]++;

	if(grid_[newCoord] == 2) ++numOverlaps_;
}
