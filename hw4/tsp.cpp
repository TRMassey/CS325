#include <iostream>
#include <climits>
#include <string>
#include <fstream>
#include <math.h>	//sqrt in graphEdges(), round in nearestNum
#include <cmath>	//pow in graphEdges()
#include <vector>
#include <cstdlib>  // exit
#include <ctime>    // timer, clock_per_second
#include <algorithm> // sort


// DS
struct City {
	int a;	// location id
	int b;  // coord
	int c;  // coord
};

struct Path {
	std::vector<int> route;
	int distance;
};

struct Edge {
	int vertex1;
	int vertex2;
	int weight;
};

// helper functions
struct Path TSP(std::vector<City> cities);
std::vector<Edge> graphEdges(std::vector<City> cities);
struct Path algo(int vertex, std::vector<int> vertices, std::vector<Edge> edges);


int main(int argc, char** argv) {

	std::string fin;			// reading file
	std::string fout;			// output file
	std::ifstream finStream;	// input stream
	std::ofstream foutStream;	// output stream
	int a, b, c;				// city id, coord, coord
	struct City location;		// city information
	std::vector<City> cities;		// story list of locations
	struct Path tour;			// final tour here


	// error catch with files
	if (argc < 2)
	{
		std::cout << "Not enough or invalid arguments, please try again.\n";
		exit(-1);
	}

	// Read input file
	fin = argv[1];
	finStream.open(fin.c_str());
	if(!finStream){
		std::cout << "Unable to open input file " << finStream << std::endl;
		exit(1);
	}

	// store the input file (same as makeGraph from python function)
	while(!finStream.eof()){
		finStream >> a >> b >> c;
		location.a = a;
		location.b = b;
		location.c = c;
		cities.push_back(location);
	}
	finStream.close();

	// timing begin
	clock_t start = clock();

	// algo here
	tour = TSP(cities);


	// timing end
	clock_t end = clock();
	int timing = end - start / CLOCKS_PER_SEC;

	// print for us on the screen
	std::cout << "\nTime elapsed:" << timing << "seconds\n";
    std::cout << "\nTour Length: " << tour.distance << "\n";



	// maek output file name
	fout = argv[1];
	fout.append(".tour");

    foutStream.open(fout.c_str());

    // write tour length first
    foutStream << tour.distance << "\r\n";

    // write tour route line by line
    for (int i = 0; i < tour.route.size(); i++) {
        foutStream << tour.route[i] << "\r\n";
    }

	// close file
	foutStream.close();

    return 0;
}

/**********************************************************************************
input: Paths for comparison
output: Direction for sort call
**********************************************************************************/
bool sortFunction (Path i, Path j) {
    return (i.distance < j.distance);
}

/**********************************************************************************
input: Vector of City. Each city contains id, coord, coord
output: Path with least distance. Each path has city id and total distance of path
**********************************************************************************/
struct Path TSP(std::vector<City> cities){
	Path curPath;				// receiving vector of city ids, and total distance
	std::vector<int> vertices;	// list of all city ids
	std::vector<Edge> edges;	// list of EDGE, composed of vertex1, vertex2, weight
	int vertex;					// single id
	int distance, distance2;	// variable for sorting by distance
	std::vector<Path> paths;	// list of all possible Paths for sorting
	// calcualte the edges (vetex, vertex) = weight
	edges = graphEdges(cities);

	// create a vertices list
	for(int i = 0; i < cities.size(); i++){
		vertex = cities[i].a;
		vertices.push_back(vertex);
	}

	// find current paths
	for(int j = 0; j < vertices.size(); j++){
		vertex = vertices[j];
		curPath = algo(vertex, vertices, edges);
		paths.push_back(curPath);	// add new path
	}

	// sort to find the least costly path
	/** figure out what is going on with this one **/
	//sort(paths.begin(), paths.end(), [](const Path& lhs, const Path& rhs){ return lhs.distance < rhs.distance; });
	std::sort( paths.begin( ), paths.end( ), sortFunction);

	// returning path with least distance
	return paths[0];
}

/**********************************************************************************************
Main algo
input: current city (vertex), list of all other cities (vertices), and a list of edges composed
of vertex1, vertex2, and weight
Output: returns a path, composed of a list of cities visited and total distance
***********************************************************************************************/
struct Path algo(int vertex, std::vector<int> vertices, std::vector<Edge> edges){
	int curVert = vertex;						// current vertex
	int minVert, minEdge;						// minimums found
	std::vector<int> unvisited(vertices);		// unvisited vertices
	Path curPath;								// tracking current path
	int distance;								// combined distance to final path
	int weight;									// current weight between two vertices

    // initialize curPath distance since apparently initializing in the struct is for C++ 11
    curPath.distance = 0;

	while(unvisited.size() > 0){
		// start case
		if(unvisited.size() == vertices.size()){
			curPath.route.push_back(curVert);	// add
			unvisited.pop_back();					// remove
		}

		// check all edges from current vertex
		for(int j = 0; j < unvisited.size(); j++){
			// find min edge connecting to current vertex
			if(curVert != unvisited[j]){
				// find the weight of the edge between two vertices (match them!)
				for(int i = 0; i < edges.size(); i++){
					if(edges[i].vertex1 == curVert && edges[i].vertex2 == unvisited[j])
						weight = edges[i].weight;
				}
				// found them, determine if smaller
				if(weight < minEdge){
					minEdge = edges[j].weight;
					minVert = unvisited[j];
				}
			}
		}

		// assign the minimums to the current path
		curPath.route.push_back(minVert);
		curPath.distance += minEdge;

		// upkeep
		// remove first instance of minVert in unvisited
		std::vector<int>::iterator position = std::find(unvisited.begin(), unvisited.end(), minVert);

		if (position != unvisited.end()) {  // if it reaches the end, the value doesn't exist
            unvisited.erase(position);
		}

		curVert = minVert;
		minVert = 0;
		minEdge = 0;

		// final weird end case to connect end -> start
		if(unvisited.size() == 0){
			// get the weight betweent he two nodes
			for(int i = 0; i < edges.size(); i++){
				if(edges[i].vertex1 == curVert && edges[i].vertex2 == unvisited[i])
						weight = edges[i].weight;
				}
			distance += weight;
		}
	}

	// return the Path: It has the vector of cities visited and the total distance it took
	return curPath;
}



/************************************************************************************************
input: float number
output: int rounded to the nearest non decimal place
************************************************************************************************/
int nearestInt(int num){
	return round(num);
}



/************************************************************************************************
input: vector of City elements
output: verctor of Edge elements that considers all city to city edges
************************************************************************************************/
std::vector<Edge> graphEdges(std::vector<City> cities){
	//create a vector to rep edges dictionary from py
	std::vector<Edge> edges;
	int weight;

	//iterate through all vert1
	int vert1, vert2;
	for(vert1 = 0; vert1 < sizeof(cities); vert1++){
		//iterate through all vert2
		for(vert2 = 0; vert2 < sizeof(cities); vert2++){
			//vert1 and vert2 cannot be the same
			if(vert1 != vert2){
				//make edge
				Edge curEdge;
				curEdge.vertex1 = vert1;
				curEdge.vertex2 = vert2;
				int twoB = cities[vert1].b - cities[vert2].b;
				int twoC = cities[vert1].c - cities[vert2].c;

				//calc edge weight
				curEdge.weight = nearestInt(sqrt(pow(twoB,2)+(pow(twoC,2))));
				//insert into edges vector
				edges.push_back(curEdge);
			}
		}
	}
	return edges;
}
