/*
	AnthonyN1
	Advent of Code 2021
	Day 05 - https://adventofcode.com/2021/day/5
	Coordinate Class
*/

#ifndef __coordinate_h_
#define __coordinate_h_


class Coordinate{
	public:
		// Constructor
		Coordinate(int x, int y): x_(x), y_(y) {}

		// Accessors
		int getX() const{ return x_; }
		int getY() const{ return y_; }
	private:
		int x_, y_;
};

bool operator==(const Coordinate &c1, const Coordinate &c2);

#endif