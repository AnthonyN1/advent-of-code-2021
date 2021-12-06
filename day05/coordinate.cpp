/*
	AnthonyN1
	Advent of Code 2021
	Day 05 - https://adventofcode.com/2021/day/5
	Coordinate Implementation
*/

#include "coordinate.h"


// Non-member
/*
	Returns true iff each member variable is equal.
*/
bool operator==(const Coordinate &c1, const Coordinate &c2){
	return c1.getX() == c2.getX() && c1.getY() == c2.getY();
}