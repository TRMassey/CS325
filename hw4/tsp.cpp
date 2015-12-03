#include <iostream>
#include <climits>
#include <strings>
#include <fstream>

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
	int vertex;
	int vertex2;
	int weight;
};

// helper functions
std::vector<Path> TSP(std::vector<City> cities);
struct std::vector<Edge> edges graphEdges(std::vector<City> cities);
struct Path algo(int vertex, std::vector<int> vertices, std::vector<Edge> edges);


int main(int argc, char** argv) {
	
	std::string fin;			// reading file
	std::string fout;			// output file
	std::ofstream finStream;	// input stream
	std::ofstream foutStream;	// output stream
	int a, b, c;				// city id, coord, coord
	struct City location;		// city information
	vector<City> cities;		// story list of locations
	vector<Path> tour;			// final tour here


	// error catch with files
	if (argc < 2)
	{
		usage();
		exit(-1);
	}

	// Read input file
	fin = argv[1];
	finStream.open(fin.c_str());
	if(!finStream){
		cerr << "Unable to pen input file " << finStream << std::endl;
		exit(1);
	}

	// store the input file (same as makeGraph from python function)
	while(!finStream.eof()){
		finStream >> a >> b >> c;
		location = {b, c};
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
	std::cout << "\nTour Length: " << tour[1] << "\n";

	
	// maek output file name
	fout = argv[1];
	fout.append(".tour");

	// STILL NEED TO DO: print to output file
		// while not end of tours
		// output file stream >> a >> b >> c

return 0;
}


/**********************************************************************************
input: Vector of City. Each city contains id, coord, coord
output: Path with least distance. Each path has city id and total distance of path
**********************************************************************************/
std::vector<Path> TSP(std::vector<City> cities){
	Path curPath;				// receiving vector of city ids, and total distance
	std::vetor<int> vertices;	// list of all city ids
	std::vector<Edge> edges;	// list of EDGE, composed of vertex1, vertex2, weight
	int vertex;					// single id
	int distance, distance2;	// variable for sorting by distance
	std::vector<Path> paths;	// list of all possible Paths for sorting
	// calcualte the edges (vetex, vertex) = weight
	edges = graphEdges(cities);

	// create a vertices list
	for(int i = 0; i < cities.size(); i++){
		vertex = cities.a;
		vertices.push_back(vertex);
	}

	// find current paths
	for(int j = 0; j < vertices.size(); j++){
		vertex = vertices[i];
		curPath = algo(vertex, vertices, edges);
		paths.push_back(curPath);	// add new path
	}

	// sort to find the least costly path
	sort(paths.begin(), paths.end(), [](const Path& lhs, const Path& rhs){ return lhs.distance < rhs.distance});

	// returning oath with least distance
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
	int i;										// iterator
	int weight;									// current weight between two vertices

	while(unvisited.size() > 0){
		// start case
		if(unvisited.size() == vertices.size()){
			curPath.route[i].push_back(curVert);	// add
			unvisited.pop_back();					// remove
			i++;									// iterate
		}

		// check all edges from current vertex
		for(int j = 0; j < unvisited.size(); j++){
			// find min edge connecting to current vertex
			if(curVert != unvisited[j]){
				// find the weight of the edge between two vertices (match them!)
				for(int i = 0; i < edges.size(); i++){
					if(edges.vertex1 == curVert && edges.vertex2 == unvisited[j])
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
		curPath.route[i].push_back(minVert);
		curpath.distance += minEdge;

		// upkeep
		unvisited.pop_back(minVert);
		curVert = minVert;
		minVert = 0;
		minEdge = 0;

		// final weird end case to connect end -> start
		if(unvisited.size() == 0){
			// get the weight betweent he two nodes
			for(int i = 0; i < edges.size(); i++){
				if(edges.vertex1 == curVert && edges.vertex2 == unvisited[j])
						weight = edges[i].weight;
				}
			distance += weight;
		}
	}

	// return the Path: It has the vector of cities visited and the total distance it took
	return curPath;
}


/************************************************************************************************
input:
output:
************************************************************************************************/
struct std::vector<Edge> edges graphEdges(std::vector<City> cities){

}