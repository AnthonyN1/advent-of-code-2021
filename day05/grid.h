/*
	AnthonyN1
	Advent of Code 2021
	Day 05 - https://adventofcode.com/2021/day/5
	Grid Class
*/

#ifndef __grid_h_
#define __grid_h_

#include <unordered_map>
#include <utility>

#include "coordinate.h"


class HashFunctor{
	public:
		unsigned int operator()(const Coordinate &key) const{
			unsigned int prime = 1315423919;
			return (prime + key.getX()) * (prime + key.getY());
		}
};


class Grid{
	public:
		// Constructor
		Grid(): numOverlaps_(0) {}

		// Accessor
		unsigned int getNumOverlaps() const{ return numOverlaps_; }

		// Modifier
		void addLine(const std::pair<Coordinate, Coordinate> &line);
	private:
		unsigned int numOverlaps_;
		std::unordered_map<Coordinate, unsigned int, HashFunctor> grid_;
};

#endif