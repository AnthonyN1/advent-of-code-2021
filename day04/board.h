/*
	AnthonyN1
	Advent of Code 2021
	Day 04 - https://adventofcode.com/2021/day/4
	Board Implementation
*/

#ifndef __board_h_
#define __board_h_

#include <fstream>
#include <iostream>


class Board{
	public:
		// Constructors
		Board();
		void construct(std::ifstream &file);

		// Accessors
		bool isComplete() const{ return complete_; }

		// Modifiers
		void clear();
		void mark(unsigned int num);

		// Operators
		bool operator==(const Board &other) const;

		// Misc.
		unsigned int getScore(unsigned int multiplier) const;


		void print(){
			for(unsigned int i = 0; i < size_; ++i){
				for(unsigned int j = 0; j < size_; ++j){
					std::cout << board_[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
	private:
		void checkComplete();
		bool colFilled(unsigned int c) const;
		bool rowFilled(unsigned int r) const;

		static const unsigned int size_ = 5;
		bool complete_;
		unsigned int board_[size_][size_];
		bool marks_[size_][size_];
};

#endif