/*
	AnthonyN1
	Advent of Code 2021
	Day 05 - https://adventofcode.com/2021/day/5
	Grid Implementation
*/

#include <unordered_map>
#include <utility>

#include "coordinate.h"
#include "grid.h"


// Modifier
/*
	Adds a line (using integer coordinates) to the hash map.
	Checks if the added line collides with existing lines.
*/
void Grid::addLine(const std::pair<Coordinate, Coordinate> &line){
	Coordinate c1 = line.first;
	Coordinate c2 = line.second;

	int currX = c1.getX(), currY = c1.getY();
	while(currX != c2.getX() || currY != c2.getY()){
		Coordinate newCoord(currX, currY);
		grid_[newCoord]++;

		if(grid_[newCoord] == 2) ++numOverlaps_;

		// Advances towards the second coordinate.
		if(currX != c2.getX()) currX += (c1.getX() < c2.getX()) ? 1 : -1;
		if(currY != c2.getY()) currY += (c1.getY() < c2.getY()) ? 1 : -1;
	}

	// Repeats for the second coordinate (loop condition).
	Coordinate newCoord(currX, currY);
	grid_[newCoord]++;

	if(grid_[newCoord] == 2) ++numOverlaps_;
}