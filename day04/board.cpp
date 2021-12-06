/*
	AnthonyN1
	Advent of Code 2021
	Day 04 - https://adventofcode.com/2021/day/4
	Board Implementation
*/

#include <fstream>

#include "board.h"


// Constructors
/*
	Default constructor.
*/
Board::Board(){
	complete_ = false;
	for(unsigned int r = 0; r < size_; ++r){
		for(unsigned int c = 0; c < size_; ++c){
			board_[r][c] = 0;
			marks_[r][c] = false;
		}
	}
}

/*
	Constructs the 5x5 arrays from the input file stream.
	Assumes the file contains unsigned ints separated by whitespace.
*/
void Board::construct(std::ifstream &file){
	for(unsigned int r = 0; r < size_; ++r){
		for(unsigned int c = 0; c < size_; ++c){
			unsigned int temp;
			file >> temp;
			board_[r][c] = temp;
		}
	}
}


// Modifiers
/*
	Clears all marks from the board.
*/
void Board::clear(){
	for(unsigned int r = 0; r < size_; ++r)
		for(unsigned int c = 0; c < size_; ++c)
			marks_[r][c] = false;
	
	complete_ = false;
}

/*
	Marks the specified number on the board.
*/
void Board::mark(unsigned int num){
	for(unsigned int r = 0; r < size_; ++r)
		for(unsigned int c = 0; c < size_; ++c)
			if(board_[r][c] == num)
				marks_[r][c] = true;

	checkComplete();
}


// Operators
/*
	Returns true iff the boards have the same numbers in the same positions.
	Assumes the provided boards are unique.
*/
bool Board::operator==(const Board &other) const{
	if(complete_ != other.complete_) return false;

	for(unsigned int r = 0; r < size_; ++r)
		for(unsigned int c = 0; c < size_; ++c)
			if(board_[r][c] != other.board_[r][c])
				return false;

	return true;
}


// Misc.
/*
	Calculates the score of the board.
	The score is the sum of all the unmarked numbers, multiplied by the last drawn number.
*/
unsigned int Board::getScore(unsigned int multiplier) const{
	unsigned int sum = 0;
	for(unsigned int r = 0; r < size_; ++r)
		for(unsigned int c = 0; c < size_; ++c)
			if(!marks_[r][c])
				sum += board_[r][c];
	
	return sum * multiplier;
}


// Private
/*
	Sets the member variable to true iff a row or column of the board is completely marked.
*/
void Board::checkComplete(){
	// Checks the rows of the board.
	for(unsigned int r = 0; r < size_; ++r){
		if(rowFilled(r)){
			complete_ = true;
			return;
		}
	}
	
	// Checks the columns of the board.
	for(unsigned int c = 0; c < size_; ++c){
		if(colFilled(c)){
			complete_ = true;
			return;
		}
	}
}

/*
	Returns true iff the specified column is completely filled.
*/
bool Board::colFilled(unsigned int c) const{
	for(unsigned int r = 0; r < size_; ++r)
		if(!marks_[r][c])
			return false;
	
	return true;
}

/*
	Returns true iff the specified row is completely filled.
*/
bool Board::rowFilled(unsigned int r) const{
	for(unsigned int c = 0; c < size_; ++c)
		if(!marks_[r][c])
			return false;
	
	return true;
}