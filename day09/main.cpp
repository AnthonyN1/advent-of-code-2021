/*
	AnthonyN1
	Advent of Code 2021
	Day 09 - https://adventofcode.com/2021/day/9
	Main
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<std::vector<unsigned int>> board;

struct Point{
	Point(unsigned int rIn, unsigned int cIn): r(rIn), c(cIn) {}
	unsigned int r, c;
};

bool operator==(const Point &p1, const Point &p2){ return p1.r == p2.r && p1.c == p2.c; }


/*
	Populates the vector with all points in the bounds of the board.
	Assumes each row of the board has the same size.
*/
void getNeighbors(const board &b, const Point &loc, std::vector<Point> &neighbors){
	if((int)(loc.r) - 1 >= 0) neighbors.push_back(Point(loc.r - 1, loc.c));
	if(loc.r + 1 < b.size()) neighbors.push_back(Point(loc.r + 1, loc.c));
	if((int)(loc.c) - 1 >= 0) neighbors.push_back(Point(loc.r, loc.c - 1));
	if(loc.c + 1 < b[0].size()) neighbors.push_back(Point(loc.r, loc.c + 1));
}

/*
	Returns true iff the value at the position in the board is less than its neighbors.
*/
bool isLocalMinima(const board &b, const Point &loc){
	std::vector<Point> neighbors;
	getNeighbors(b, loc, neighbors);

	unsigned int lNeighborValue = b[neighbors[0].r][neighbors[0].c];
	for(unsigned int i = 1; i < neighbors.size(); ++i)
		lNeighborValue = std::min(lNeighborValue, b[neighbors[i].r][neighbors[i].c]);
	
	return b[loc.r][loc.c] < ;
}

/*
	Recursively finds all points that lead to the local minimum.
*/
void expand(const board &b, const Point &loc, std::vector<Point> &trail, unsigned int &size){
	// Base cases.
	if(b[loc.r][loc.c] == 9) return;
	if(std::find(trail.begin(), trail.end(), loc) != trail.end()) return;

	++size;
	trail.push_back(loc);

	std::vector<Point> neighbors;
	getNeighbors(b, loc, neighbors);

	// Recurses on all neighbors that are greater than the current point.
	for(const Point &n : neighbors)
		if(b[n.r][n.c] < b[loc.r][loc.c])
			expand(b, n, trail, size);
}


unsigned int part1(const board &heightMap, std::vector<Point> &minimas){
	// Sums the risk levels of all local minima.
	unsigned int sum = 0;
	for(unsigned int r = 0; r < heightMap.size(); ++r){
		for(unsigned int c = 0; c < heightMap[r].size(); ++c){
			Point current(r, c);
			if(isLocalMinima(heightMap, current)){
				minimas.push_back(current);
				sum += heightMap[current.r][current.c] + 1;
			}
		}
	}
	
	return sum;
}

unsigned int part2(const board &heightMap, const std::vector<Point> &minimas){
	// Gets the sizes of each basin.
	std::vector<unsigned int> sizes;
	for(const Point &loc : minimas){
		unsigned int size = 0;
		std::vector<Point> trail;

		expand(heightMap, loc, trail, size);
		sizes.push_back(size);
	}

	std::sort(sizes.begin(), sizes.end());

	// Finds the product of the largest three sizes.
	unsigned int product = 1;
	for(unsigned int i = 0; i < 3; ++i){
		product *= sizes.back();
		sizes.pop_back();
	}
	
	return product;
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

	// Populates a 2D vector with values from the file.
	// Assumes the file contains integers between 0 and 9.
	board heightMap;
	std::string temp;
	while(std::getline(file, temp)){
		std::vector<unsigned int> row;

		std::stringstream stream(temp);
		char height;
		while(stream >> height)
			row.push_back(height - '0');
		
		heightMap.push_back(row);
	}
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nWhat is the sum of the risk levels of all low points on your heightmap?" << std::endl;
	std::vector<Point> minimas;
	std::cout << part1(heightMap, minimas) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nWhat do you get if you multiply together the sizes of the three largest basins?" << std::endl;
	std::cout << part2(heightMap, minimas) << std::endl;

	return 0;
}
