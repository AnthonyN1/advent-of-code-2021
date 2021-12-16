/*
	AnthonyN1
	Advent of Code 2021
	Day 16 - https://adventofcode.com/2021/day/16
	Packet Implementation
*/

#include <cmath>
#include <limits>
#include <vector>

#include "packet.h"


// Constructor
/*
	Constructs a Packet from a binary number.
	Assumes the vector only contains ones and zeros.
	Assumes the vector is formatted MSB->LSB.
*/
Packet::Packet(const bin_num &bin){
	version_ = binToDec(bin, 0, 2);
	typeID_ = binToDec(bin, 3, 5);

	if(typeID_ == 4){
		// If the type ID is 4, the packet is a literal.
		size_ = 6;
		subPackets_ = std::vector<Packet>();
		parseLiteral(bin);
	} else{
		// Else, it's an operator.
		size_ = 7;
		parseSubPackets(bin);
		calculateValue();
	}
}


// Accessor
/*
	Sums the version numbers of the outer packet and its sub-packets (if any).
*/
unsigned int Packet::sumVersions() const{
	unsigned int sum = version_;
	for(const Packet &p : subPackets_)
		sum += p.sumVersions();
	
	return sum;
}


// Private
/*
	Converts a binary number to its decimal representation.
	Assumes 'start' and 'end' are in-bounds.
*/
unsigned long long Packet::binToDec(const bin_num &bin, unsigned int start, unsigned int end) const{
	unsigned long long num = 0;
	for(unsigned int i = end; i >= start && i <= end; --i)
		num += bin[i] * (unsigned long long)(pow(2, end - i));
	
	return num;
}

/*
	Parses the literal portion of the packet.
*/
void Packet::parseLiteral(const bin_num &bin){
	bin_num literalBin;
	unsigned int markerIdx = 1;
	do{
		size_ += 5;

		markerIdx += 5;

		// Adds the 4 non-marker bits to the literal binary number.
		literalBin.push_back(bin[markerIdx + 1]);
		literalBin.push_back(bin[markerIdx + 2]);
		literalBin.push_back(bin[markerIdx + 3]);
		literalBin.push_back(bin[markerIdx + 4]);
	} while(bin[markerIdx] == 1);

	value_ = binToDec(literalBin);
}

/*
	Parses the sub-packets of an operator packet.
*/
void Packet::parseSubPackets(const bin_num &bin){
	unsigned int lengthTypeID = bin[6];

	if(lengthTypeID == 0){
		// If the length type ID is 0, the next 15 bits are the total number of remaining bits.
		size_ += 15;
		unsigned int totalBits = size_ + binToDec(bin, 7, 21);

		// Parses the sub-packets.
		while(size_ < totalBits){
			Packet nextP(bin_num(bin.begin() + size_, bin.end()));
			subPackets_.push_back(nextP);

			size_ += nextP.size_;
		}
	} else{
		// Else, the next 11 bits are the total number of sub-packets left.
		size_ += 11;
		unsigned int remPackets = binToDec(bin, 7, 17);

		// Parses the sub-packets.
		for(unsigned int i = 0; i < remPackets; ++i){
			Packet nextP(bin_num(bin.begin() + size_, bin.end()));
			subPackets_.push_back(nextP);

			size_ += nextP.size_;
		}
	}
}

/*
	Calculates the value of an operator packet.
	Assumes that greater than, less than, or equal to packets have exactly 2 sub-packets.
*/
void Packet::calculateValue(){
	switch(typeID_){
		case 0:
			// Sum packet.
			value_ = 0;
			for(const Packet &p : subPackets_)
				value_ += p.value_;
			
			break;
		case 1:
			// Product packet.
			value_ = 1;
			for(const Packet &p : subPackets_)
				value_ *= p.value_;
			
			break;
		case 2:
			// Minimum packet.
			value_ = std::numeric_limits<unsigned long long>::max();
			for(const Packet &p : subPackets_)
				if(p.value_ < value_)
					value_ = p.value_;
			
			break;
		case 3:
			// Maximum packet.
			value_ = 0;
			for(const Packet &p : subPackets_)
				if(p.value_ > value_)
					value_ = p.value_;
			
			break;
		case 5:
			// Greater than packet.
			value_ = subPackets_[0].value_ > subPackets_[1].value_ ? 1 : 0;

			break;
		case 6:
			// Less than packet.
			value_ = subPackets_[0].value_ < subPackets_[1].value_ ? 1 : 0;

			break;
		case 7:
			// Equal to packet.
			value_ = subPackets_[0].value_ == subPackets_[1].value_ ? 1 : 0;

			break;
	}
}