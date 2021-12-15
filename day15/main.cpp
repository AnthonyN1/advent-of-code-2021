/*
	AnthonyN1
	Advent of Code 2021
	Day 01 - https://adventofcode.com/2021/day/1
	Main
*/

#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<std::vector<unsigned int>> grid;
typedef std::pair<unsigned int, unsigned int> point;
typedef std::pair<unsigned int, point> q_pair;


/*
	Gets all neighboring elements, excluding the diagonals.
*/
void getNeighbors(const grid &g, const point &u, std::vector<point> &verts){
	unsigned int r = u.first, c = u.second;

	if(r > 0) verts.push_back(point(r - 1, c));
	if(r < g.size() - 1) verts.push_back(point(r + 1, c));
	if(c > 0) verts.push_back(point(r, c - 1));
	if(c < g[r].size() - 1) verts.push_back(point(r, c + 1));
}

/*
	Runs Dijkstra's algorithm, stopping when the bottom-right corner of the grid is reached.
*/
unsigned int dijkstra(const grid &g){
	point start(0, 0);
	point end(g.size() - 1, g[g.size() - 1].size() - 1);

	// Initializes a map of total risk from the top-left.
	std::map<point, unsigned int> risk;
	for(unsigned int r = 0; r < g.size(); ++r)
		for(unsigned int c = 0; c < g[r].size(); ++c)
			risk[point(r, c)] = std::numeric_limits<unsigned int>::max();
	risk[start] = 0;

	// Initializes a min-heap priority queue of vertices to process.
	std::priority_queue<q_pair, std::vector<q_pair>, std::greater<q_pair>> Q;
	Q.push(q_pair(0, start));

	// Loops until the priority queue is empty.
	while(!Q.empty()){
		// Pops the minimum distance element from the priority queue.
		point u = Q.top().second;
		Q.pop();

		// If Dijstra's has reached the end, return.
		if(u == end) return risk[u];

		// Loops through all edges of u, and updates lowest risk accordingly.
		std::vector<point> verts;
		getNeighbors(g, u, verts);
		for(const point &v : verts){
			if(risk[v] > risk[u] + g[v.first][v.second]){
				risk[v] = risk[u] + g[v.first][v.second];
				Q.push(q_pair(risk[v], v));
			}
		}
	}

	// Dijkstra's should never get here. The end will always be visited.
	return 0;
}

/*
	Expands the vector out to 5 times its original size.
*/
void expandRight(std::vector<unsigned int> &row){
	unsigned int origSize = row.size();
	for(unsigned int i = origSize; i < 5 * origSize; ++i){
		if(row[i - origSize] == 9) row.push_back(1);
		else row.push_back(row[i - origSize] + 1);
	}
}

/*
	Increments each element in the vector by 1, wrapping around from 9 to 1.
*/
void increment(std::vector<unsigned int> &row){
	for(unsigned int &ele : row){
		if(ele == 9) ele = 1;
		else ele += 1;
	}
}

/*
	Expands the grid to a 5x5 grid.
*/
void expand(grid &g){
	// Expands the first sub-grid to the right.
	for(std::vector<unsigned int> &r : g)
		expandRight(r);
	
	// Expands the first five sub-grids down.
	unsigned int origSize = g.size();
	for(unsigned int r = origSize; r < 5 * origSize; ++r){
		std::vector<unsigned int> newRow(g[r - origSize]);
		increment(newRow);
		g.push_back(newRow);
	}
}


unsigned int part1(const grid &g){
	// Finds the path of lowest risk.
	return dijkstra(g);
}

unsigned int part2(grid &g){
	// Expands the grid, then finds the path of lowest risk.
	expand(g);
	return dijkstra(g);
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
	// Assumes the file contains non-negative single-digit integers.
	grid g;
	std::string temp;
	while(file >> temp){
		std::vector<unsigned int> row;
		for(char c : temp)
			row.push_back(c - '0');
		
		g.push_back(row);
	}
	
	file.close();
	

	// Part 1
	std::cout << "Part 1:\nWhat is the lowest total risk of any path from the top left to the bottom right?" << std::endl;
	std::cout << part1(g) << std::endl;

	std::cout << std::endl;

	// Part 2
	std::cout << "Part 2:\nUsing the full map, what is the lowest total risk of any path from the top left to the bottom right?" << std::endl;
	std::cout << part2(g) << std::endl;

	return 0;
}
