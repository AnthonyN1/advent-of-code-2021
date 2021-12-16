/*
	AnthonyN1
	Advent of Code 2021
	Day 13 - https://adventofcode.com/2021/day/13
	Paper Implementation
*/

#include <iostream>
#include <set>
#include <vector>

#include "paper.h"


// Modifiers
/*
	Folds the paper to the left along the specified line perpendicular to the x-axis.
	Assumes no dots lie on the line.
*/
void Paper::foldX(unsigned int line){
	std::vector<coord> newDots;

	std::set<coord>::iterator itr = dots_.begin();
	while(itr != dots_.end()){
		if(itr->first > line){
			unsigned int newX = (2 * line) - itr->first;
			newDots.push_back({newX, itr->second});

			itr = dots_.erase(itr);
		} else{
			++itr;
		}
	}

	for(const coord &dot : newDots)
		dots_.insert(dot);
}

/*
	Folds the paper down along the specified line perpendicular to the y-axis.
	Assumes no dots lie on the line.
*/
void Paper::foldY(unsigned int line){
	std::vector<coord> newDots;

	std::set<coord>::iterator itr = dots_.begin();
	while(itr != dots_.end()){
		if(itr->second > line){
			unsigned int newY = (2 * line) - itr->second;
			newDots.push_back({itr->first, newY});

			itr = dots_.erase(itr);
		} else{
			++itr;
		}
	}

	for(const coord &dot : newDots)
		dots_.insert(dot);
}


// Misc.
/*
	Prints ASCII-art to standard output.
*/
void Paper::print() const{
	unsigned int maxX = 0, maxY = 0;
	for(const coord &c : dots_){
		if(c.first > maxX) maxX = c.first;
		if(c.second > maxY) maxY = c.second;
	}

	for(unsigned int y = 0; y <= maxY; ++y){
		for(unsigned int x = 0; x <= maxX; ++x){
			if(dots_.find({x, y}) != dots_.end()) std::cout << '#';
			else std::cout << '.';
		}
		std::cout << std::endl;
	}
}
