/*
	AnthonyN1
	Advent of Code 2021
	Day 16 - https://adventofcode.com/2021/day/16
	Packet Class
*/

#ifndef __packet_h_
#define __packet_h_

#include <vector>

typedef std::vector<unsigned int> bin_num;


class Packet{
	public:
		// Constructor
		Packet(const bin_num &bin);

		// Accessors
		unsigned int sumVersions() const;
		unsigned long long getValue() const{ return value_; }
	private:
		unsigned long long binToDec(const bin_num &bin) const{ return binToDec(bin, 0, bin.size() - 1); }
		unsigned long long binToDec(const bin_num &bin, unsigned int start, unsigned int end) const;
		void parseLiteral(const bin_num &bin);
		void parseSubPackets(const bin_num &bin);
		void calculateValue();

		unsigned int version_, typeID_;
		unsigned int size_;
		unsigned long long value_;
		std::vector<Packet> subPackets_;
};

#endif