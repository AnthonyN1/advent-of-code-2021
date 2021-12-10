/*
	AnthonyN1
	Advent of Code 2021
	Day 08 - https://adventofcode.com/2021/day/8
	Main
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<std::vector<std::string>, std::vector<std::string>> data_line;
typedef std::vector<std::set<char>> display_intersections;
typedef std::map<char, unsigned int> d_map;
typedef std::set<unsigned int> true_display;

/*
	Hardcodes the seven-segment display of the numbers 0 through 9, using the following layout:
	 1111
	2	 3
	2	 3
	 4444
	5	 6
	5	 6
	 7777
*/
const true_display SEG_0{1, 2, 3, 5, 6, 7};
const true_display SEG_1{3, 6};
const true_display SEG_2{1, 3, 4, 5, 7};
const true_display SEG_3{1, 3, 4, 6, 7};
const true_display SEG_4{2, 3, 4, 6};
const true_display SEG_5{1, 2, 4, 6, 7};
const true_display SEG_6{1, 2, 4, 5, 6, 7};
const true_display SEG_7{1, 3, 6};
const true_display SEG_8{1, 2, 3, 4, 5, 6, 7};
const true_display SEG_9{1, 2, 3, 4, 6, 7};


/*
	Decodes the displays, storing the results in a d_map.
	Assumes the only letters used are 'a' through 'g'.
*/
void decodeLine(const display_intersections &inters, d_map &decodeMap){
	std::set<char> collector;

	// True 'a' segment.
	std::set_difference(inters[3].begin(), inters[3].cend(), inters[2].cbegin(), inters[2].cend(), std::inserter(collector, collector.begin()));
	char a = *(collector.begin());
	decodeMap[a] = 1;

	// True 'd' segment.
	collector.clear();
	std::set_intersection(inters[5].cbegin(), inters[5].cend(), inters[4].cbegin(), inters[4].cend(), std::inserter(collector, collector.begin()));
	char d = *(collector.begin());
	decodeMap[d] = 4;

	// True 'g' segment.
	collector = inters[5];
	collector.erase(a);
	collector.erase(d);
	char g = *(collector.begin());
	decodeMap[g] = 7;

	// True 'e' segment.
	collector.clear();
	std::set_difference(inters[7].cbegin(), inters[7].cend(), inters[4].cbegin(), inters[4].cend(), std::inserter(collector, collector.begin()));
	collector.erase(a);
	collector.erase(g);
	char e = *(collector.begin());
	decodeMap[e] = 5;

	// True 'b' segment.
	collector.clear();
	std::set_difference(inters[4].cbegin(), inters[4].cend(), inters[2].cbegin(), inters[2].cend(), std::inserter(collector, collector.begin()));
	collector.erase(d);
	char b = *(collector.begin());
	decodeMap[b] = 2;

	// True 'c' segment.
	collector.clear();
	std::set_difference(inters[7].cbegin(), inters[7].cend(), inters[6].cbegin(), inters[6].cend(), std::inserter(collector, collector.begin()));
	collector.erase(d);
	collector.erase(e);
	char c = *(collector.begin());
	decodeMap[c] = 3;

	// True 'f' segment.
	collector = inters[2];
	collector.erase(c);
	char f = *(collector.begin());
	decodeMap[f] = 6;
}

/*
	Decodes the display into a recognizable seven-segment display using the provided map.
	Assumes the resulting seven-segment display is a valid numeric.
*/
std::string decodeDisplay(const std::string &dis, const d_map &decodeMap){
	true_display decodedSegment;
	for(d_map::const_iterator itr = decodeMap.cbegin(); itr != decodeMap.cend(); ++itr)
		if(std::find(dis.cbegin(), dis.cend(), itr->first) != dis.cend())
			decodedSegment.insert(itr->second);
	
	if(decodedSegment == SEG_0) return "0";
	if(decodedSegment == SEG_1) return "1";
	if(decodedSegment == SEG_2) return "2";
	if(decodedSegment == SEG_3) return "3";
	if(decodedSegment == SEG_4) return "4";
	if(decodedSegment == SEG_5) return "5";
	if(decodedSegment == SEG_6) return "6";
	if(decodedSegment == SEG_7) return "7";
	if(decodedSegment == SEG_8) return "8";
	if(decodedSegment == SEG_9) return "9";
	else return "-";
}

/*
	Returns true iff the characters is in all the strings in the vector.
*/
bool inAll(char ch, std::vector<std::string> &displays){
	if(displays.size() == 0) return false;

	for(const std::string &dis : displays){
		if(std::find(dis.cbegin(), dis.cend(), ch) == dis.cend()){
			return false;
		}
	}
	
	return true;
}

/*
	Populates a vector, where each element is a set of shared characters between the displays of that size.
*/
void collect(const std::vector<std::string> &displays, display_intersections &inters){
	std::vector<std::vector<std::string>> tempStore(8);
	for(const std::string &dis : displays)
		tempStore[dis.size()].push_back(dis);
	
	for(unsigned int i = 0; i < tempStore.size(); ++i)
		for(char ch = 'a'; ch <= 'g'; ++ch)
			if(inAll(ch, tempStore[i]))
				inters[i].insert(ch);
}


unsigned int part1(const std::vector<data_line> &lines){
	// Counts the number of times the digits 1, 4, 7, or 8 appear in the output values.
	unsigned int count = 0;
	for(const data_line &line : lines)
		for(const std::string &dis : line.second)
			if(dis.size() == SEG_1.size() || dis.size() == SEG_4.size() || dis.size() == SEG_7.size() || dis.size() == SEG_8.size())
				++count;
	
	return count;
}

unsigned int part2(const std::vector<data_line> &lines){
	// Sums up the output value of each data_line.
	unsigned int sum = 0;
	for(const data_line &line : lines){
		// Assumes the displays only have the letters 'a' through 'g'.
		d_map decodeMap{{'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0}, {'g', 0}};

		display_intersections inters(8);
		collect(line.first, inters);
		decodeLine(inters, decodeMap);

		// Decodes the output value based on the map.
		std::string decodedValue;
		for(const std::string &dis : line.second)
			decodedValue += decodeDisplay(dis, decodeMap);
		sum += std::stoi(decodedValue);
	}

	return sum;
}


/*
	Parses a string into a vector of strings.
*/
void parsePartition(const std::string &part, std::vector<std::string> &displays){
	std::stringstream partStream(part);

	std::string disStr;
	while(partStream >> disStr)
		displays.push_back(disStr);
}

/*
	Parses a string into a data_line.
	Assumes the string contains alphabetic strings separated by whitespace, partitioned into two sections by ' | '.
*/
void parse(const std::string &str, data_line &line){
	unsigned int delimLoc = str.find('|');

	// Parses the first partition.
	std::string first = str.substr(0, delimLoc - 1);
	std::vector<std::string> sigPatterns;
	parsePartition(first, sigPatterns);

	// Parses the second partition.
	std::string second = str.substr(delimLoc + 2);
	std::vector<std::string> outputVal;
	parsePartition(second, outputVal);

	line = std::make_pair(sigPatterns, outputVal);
}


int main(int argc, char* argv[]){
	// Error checking: correct number of arguments.
	if(argc != 2){
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		std::cerr << "       Usage: ./main.exe <input_file>\n";
		std::cerr << "       Exiting..." << std::endl;
		return -1;
	}

	// Initializes the input stream.
	// Error checking: successfully opened the file.
	std::ifstream file(argv[1]);
	if(!file.is_open()){
		std::cerr << "ERROR: Unable to open input file.\n";
		std::cerr << "       Exiting..." << std::endl;
		return -1;
	}

	// Populates a vector with values from the file.
	std::vector<data_line> lines;
	std::string temp;
	while(std::getline(file, temp)){
		data_line line;
		parse(temp, line);
		lines.push_back(line);
	}
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nIn the output values, how many times do digits 1, 4, 7, or 8 appear?" << std::endl;
	std::cout << part1(lines) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat do you get if you add up all of the output values?" << std::endl;
	std::cout << part2(lines) << std::endl;

	return 0;
}
