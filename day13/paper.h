/*
	AnthonyN1
	Advent of Code 2021
	Day 13 - https://adventofcode.com/2021/day/13
	Paper Class
*/

#ifndef __paper_h_
#define __paper_h_

#include <set>
#include <utility>

typedef std::pair<unsigned int, unsigned int> coord;


class Paper{
	public:
		// Accessor
		unsigned int getDots() const{ return dots_.size(); }

		// Modifiers
		void addDot(unsigned int x, unsigned int y){ dots_.insert({x, y}); }
		void foldX(unsigned int line);
		void foldY(unsigned int line);

		// Misc.
		void print() const;
	private:
		std::set<coord> dots_;
};

#endif