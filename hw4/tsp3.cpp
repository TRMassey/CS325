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

struct finalPath {
	int city;
	bool visited;
};

// helper functions
struct Path TSP(std::vector<City> cities);
std::vector<Edge> graphEdges(std::vector<City> cities);
struct Path algo(int vertex, std::vector<City> vertices, std::vector<Edge> edges);
int calcDist(City one, City two);

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


/************************************************************************************************
input: float number
output: int rounded to the nearest non decimal place
************************************************************************************************/
int nearestInt(int num){
	return round(num);
}

/**********************************************************************************
input: Vector of City. Each city contains id, coord, coord
output: Path with least distance. Each path has city id and total distance of path
**********************************************************************************/
struct Path TSP(std::vector<City> cities){
	Path curPath;				// receiving vector of city ids, and total distance
	std::vector<City> vertices;	// list of all city ids
	std::vector<Edge> edges;	// list of EDGE, composed of vertex1, vertex2, weight
	int vertex;					// single id
	int distance, distance2;	// variable for sorting by distance
	std::vector<Path> paths;	// list of all possible Paths for sorting
	// calcualte the edges (vetex, vertex) = weight
	edges = graphEdges(cities);

/*	for (int k = 0; k < edges.size(); k++) {
       std::cout << "Vertex1: " << edges[k].vertex1 << std::endl;
       std::cout << "Vertex2: " << edges[k].vertex2 << std::endl;
       std::cout << "Weight: " << edges[k].weight << std::endl;
	}*/

	//create a vertices list
	for(int i = 0; i < cities.size() -1; i++){
		vertices.push_back(cities[i]);
		//std::cout << "vertices[i] " << vertices[i];
	}

/*	for(int i = 0; i < vertices.size(); i++){
		std::cout << "Vertices at " << i << ": " << vertices[i] << "\n";

	}*/

	// find current paths
	for(int j = 0; j < vertices.size(); j++){
		vertex = cities[j].a;
		curPath = algo(vertex, vertices, edges);
		paths.push_back(curPath);	// add new path
	}

/*		for(int i = 0; i < paths.size(); i++){
			std::cout << "Path Route: \n";
			for(int j = 0; j < paths[i].route.size(); j++){
				std::cout << paths[i].route[j] << ", ";
			}
			std::cout << "\n";

		std::cout << "Distance: " << paths[i].distance << "\n";*/

	//}

	// sort to find the least costly path
	/** figure out what is going on with this one **/
	//sort(paths.begin(), paths.end(), [](const Path& lhs, const Path& rhs){ return lhs.distance < rhs.distance; });
	std::sort( paths.begin( ), paths.end( ), sortFunction);

//recalculate path 
/*	int recalc = 0;
	int i;
	for(i=0; i < paths[0].route.size()-1; i++){
		int x = cities[paths[0].route[i]].b - cities[paths[0].route[i+1]].b;
		int y = cities[paths[0].route[i]].c - cities[paths[0].route[i+1]].c;
		recalc += nearestInt(sqrt(pow(x,2)+(pow(y,2))));
		//std::cout << cities[i].a << std::endl;
		std::cout << cities[paths[0].route[i]].a << ", " << cities[paths[0].route[i+1]].a << ": " << nearestInt(sqrt(pow(x,2)+(pow(y,2)))) << std::endl;
	}
	int x = cities[paths[0].route.size()-2].b - cities[paths[0].route[0]].b;
	int y = cities[paths[0].route.size()-2].c - cities[paths[0].route[0]].c;
	recalc += nearestInt(sqrt(pow(x,2)+pow(y,2)));
	std::cout << cities[paths[0].route.size()-2].a << ", " << cities[paths[0].route[0]].a << ": " << nearestInt(sqrt(pow(x,2)+(pow(y,2)))) << std::endl;

	paths[0].distance = recalc;
*/
/*
	int i;
	for(i=0; i < paths[0].route.size()-1; i++){
		int x = cities[i].b - cities[i+1].b;
		int y = cities[i].c - cities[i+1].c;
		recalc += nearestInt(sqrt(pow(x,2)+(pow(y,2))));
		std::cout << recalc << std::endl;
	}
*/

	// returning path with least distance
	return paths[0];
}

int calcDist(City one, City two){
	int dist = round(sqrt(pow(one.b - two.b,2)+(pow(one.c - two.c,2))));
	return dist;
}
/**********************************************************************************************
Main algo
input: current city (vertex), list of all other cities (vertices), and a list of edges composed
of vertex1, vertex2, and weight
Output: returns a path, composed of a list of cities visited and total distance
***********************************************************************************************/
struct Path algo(int vertex, std::vector<City> vertices, std::vector<Edge> edges){
	int curVert = vertex;						// current vertex
	int minVert, minEdge;						// minimums found
	Path curPath;								// tracking current path
	int distance;								// combined distance to final path
	int weight;									// current weight between two vertices
	City vertexCity;
	City unvisitedCity;

    // initialize curPath distance since apparently initializing in the struct is for C++ 11
    curPath.distance = 0;
    std::vector<City> unvisited;

    for(int i = 0; i < vertices.size(); i++){
    	unvisited.push_back(vertices[i]);
    	if(vertices[i].a == vertex){
    		vertexCity.a = vertices[i].a;
    		vertexCity.b = vertices[i].b;
    		vertexCity.c = vertices[i].c;
    		unvisitedCity.a = vertexCity.a;
    		unvisitedCity.b = vertexCity.b;
    		unvisitedCity.c = vertexCity.c;
    	}
    }


   curVert = vertex;
   while(!unvisited.empty()){
   		minEdge = 1000000;
   		for(int i=0; i < unvisited.size(); i++){
   			distance = calcDist(unvisitedCity, unvisited[i]);
   			if(distance < minEdge){
   				minEdge = distance;
   				minVert = i;
   			}
   		}
   		unvisitedCity = unvisited[minVert];
   		curVert = unvisited[minVert].a;
   		curPath.route.push_back(curVert);
   		curPath.distance += minEdge;
   		unvisited.erase(unvisited.begin()+minVert);
   }

   // end stuff
   distance = calcDist(unvisitedCity, vertexCity);
   curPath.distance += distance;
	// return the Path: It has the vector of cities visited and the total distance it took
	return curPath;
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

	for(vert1 = 0; vert1 < cities.size()-1; vert1++){
		//iterate through all vert2
		for(vert2 = 0; vert2 < cities.size()-1; vert2++){
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
