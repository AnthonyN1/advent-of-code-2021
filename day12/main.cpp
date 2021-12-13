/*
	AnthonyN1
	Advent of Code 2021
	Day 12 - https://adventofcode.com/2021/day/12
	Main
*/

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

typedef std::map<std::string, std::set<std::string>> adj_list;


/*
	Counts the number of paths from start to end, where nodes that are all lowercase can only be visited once.
	Assumes only one node in the graph is labeled "start", and one for "end".
	Assumes there's a non-zezro finite number of distinct paths from "start" to "end".
	Assumes cave labels are either all capital letters or all lowercase letters.
*/
unsigned int getPathsP1(const adj_list &caves, const std::string &node, std::set<std::string> &smallCaves){
	// Base cases.
	if(node == "end") return 1;
	if(smallCaves.find(node) != smallCaves.end()) return 0;

	// Caves that are labeled with lowercase letters are small.
	if(node[0] >= 'a' && node[0] <= 'z') smallCaves.insert(node);

	unsigned int paths = 0;
	for(const std::string &v : caves.at(node))
		paths += getPathsP1(caves, v, smallCaves);
	
	smallCaves.erase(node);
	return paths;
}

/*
	Counts the number of paths from start to end, where nodes that are all lowercase can only be visited once, 
	except for one, which can be visited twice.
	See above for assumptions.
*/
unsigned int getPathsP2(const adj_list &caves, const std::string &node, std::string &secondSmallCave, std::set<std::string> &smallCaves){
	// Base cases.
	if(node == "end") return 1;

	bool justChanged = false;
	if(smallCaves.find(node) != smallCaves.end()){
		if(secondSmallCave == ""){
			secondSmallCave = node;
			justChanged = true;
		} else{
			return 0;
		}
	}

	// Caves that are labeled with lowercase letters are small.
	if(node[0] >= 'a' && node[0] <= 'z') smallCaves.insert(node);

	unsigned int paths = 0;
	for(const std::string &v : caves.at(node))
		paths += getPathsP2(caves, v, secondSmallCave, smallCaves);
	
	if(node != secondSmallCave || !justChanged) smallCaves.erase(node);
	if(justChanged) secondSmallCave = "";
	
	return paths;
}


unsigned int part1(const adj_list &caves){
	// Counts the number of distinct paths from start to end.
	std::string node("start");
	std::set<std::string> smallCaves;
	return getPathsP1(caves, node, smallCaves);
}

unsigned int part2(const adj_list &caves){
	// Counts the number of distinct paths from start to end.
	std::string node("start");
	std::string secondSmallCave("");
	std::set<std::string> smallCaves;
	return getPathsP2(caves, node, secondSmallCave, smallCaves);
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

	// Populates an adjacency list with values from the file.
	adj_list caves;

	std::string line;
	while(file >> line){
		// Assumes the file contains strings on each line, partitioned by a '-'.
		unsigned int delimLoc = line.find('-');

		std::string u = line.substr(0, delimLoc);
		std::string v = line.substr(delimLoc + 1);

		// DFS should never attempt to go back to the start, or continue from the end.
		if(u != "end" && v != "start") caves[u].insert(v);
		if(u != "start" && v != "end") caves[v].insert(u);
	}
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nHow many paths through this cave system are there that visit small caves at most once?" << std::endl;
	std::cout << part1(caves) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nGiven these new rules, how many paths through this cave system are there?" << std::endl;
	std::cout << part2(caves) << std::endl;

	return 0;
}
