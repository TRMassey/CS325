'''
 Alt version to main.py
'''
import sys
import os
import math
import time


#route must be an array of some kind, i is start, j is end
# removing edges and reconnecting
def twoOptSwap(route, i, j): 
	for k in range(i, len(route)):
		routeTwo[counter] = route[k]
		newRoute(reversed(routeTwo))
	return newRoute


def optimize(graph, route, currentDistance):

	bestDistance = currentDistance
	for i in range(1, len(route) - 1):
		#positions
		one = i;
		two = i+1 % len(route)

		for j in range(i + 1, len(route)):

			three = j % len(route)
			four = j+1 % len(route)

			#paths
			pathOne = route[one]
			pathTwo = route[two]
			pathThree = route[three]
			pathFour = route[four]


			#determine shortest
			if (graph[pathOne][pathThree] + graph[pathTwo][pathFour]) < (graph[pathOne][pathTwo] + graph[pathThree][pathFour]):
				new_distance = currentDistance
				new_distance -= (graph[pathOne][pathTwo] + graph[pathThree][pathFour] - graph[pathOne][pathThree] + graph[pathTwo][pathFour])

				#reverse and swap per wikipedia, removing edge
				new_route = twoOptSwap(route, i + 1, j)

				if new_distance < bestDistance:
					bestDistance = new_distance

				if bestDistance == currentDist:
					break

	return bestDistance


def makeGraph():
    # make a list of the values as they are read in
	# since the number of the cities corresponds with its position in the list, that value is not saved
	coordList = list()	
	filename = sys.argv[1]
	
	with open(filename) as f:
		for line in f:
			splitter = line.split()
			coord = (splitter[1], splitter[2])
			coordList.append(coord)

	return coordList



# Description: To avoid floating point precision problems 
# in computing the squareroot, we will always round the 
# distance to the nearest integer 
# Parmeters: float number
# Return: integer      
def nearestInt(num):
    if num-int(num) >= .5:
        return int(num)+1
    else:
        return int(num) 



# Description: takes given list and calculates edges to/from 
# all v
# Parmeters: Graph in format from func makeGraph()
# Return: dict of key=(vertex#,vertex#), value = edge weight 
def graphEdges(G):
    lowRange = 0
    edges  = dict()
    #iterate through all start points
    for vertex1 in range(0, len(G)):
        lowRange += 1
        #iterate through all end points
        for vertex2 in [x for x in xrange(len(G)) if x != vertex1]:
            #this is from assignment description
            edges[(int(vertex1),int(vertex2))] = nearestInt(math.sqrt(((int(G[vertex1][0])-int(G[vertex2][0]))**2)+((int(G[vertex1][1])-int(G[vertex2][1]))**2)))
    #dict of key=(vertex#,vertex#), value = edge weight 
    return edges



def greedyPath(vertex, vertices, edges):
	curVert = vertex # current vertex being considered
	minEdge = float("inf") #compare mins when iterating
	minVert = None	#compare mins when iterating
	path = list() # list of decided path for tsp
	distance = 0	#combined distance of final path
	unvisited = list(vertices) #keeps track of what still needs to be used

	#create a path with all vertices
	while len(unvisited) > 0:
		#start case: no path started yet
		if len(unvisited) == len(vertices):
			path.append(curVert)
			unvisited.remove(vertex)
		#check all edges from current vertex
		for vert in unvisited: #must be to unused vertex
			#find min edge connecting to curent vertex
			if edges[curVert,vert] < minEdge:
				#update to new min
				minEdge = edges[curVert,vert] 
				minVert = vert
		#use min info for official path info
		path.append(minVert)
		distance += minEdge
		#upkeep for iteration
		unvisited.remove(minVert)
		curVert = minVert
		minVert = None
		minEdge = float("inf")
		#end case: make cycle and connect end->start
		if len(unvisited) == 0:
			distance += edges[curVert, vertex]
	return (path, distance)



def tsp(G):
	path = list()
	vertices = list()

	#calculate edges  (vertex, vertex) = weight
	edges = graphEdges(G)
	
	#create vertices list
	for vertex in G:
		vertices.append(G.index(vertex))
	
	for vertex in vertices:
		path.append(greedyPath(vertex, vertices, edges))	#parameters might need to change

	#get the optimal path in first index
	path.sort(key=lambda tup:tup[1])
### not sure about above parameters, need to lookup

	return path[0]



def main():
    # Your program must:
    # Accept problem instances on the command line
    f = open(sys.argv[1], "r")
    inputname = sys.argv[1]
    G = makeGraph()
    #print G
    f.close()   

	# timer needed
    start = time.time()
    # this is where we would call the algorithm
    tour = tsp(G)
    distance = optimize(G, tour, tour[1])

    end = time.time()

    print "Time elapsed:",(end - start), "seconds"

    print "Tour length:", distance

    # Name the output file as the input file's name with .tour appended 
    outputname = inputname + ".tour"

    out = open(outputname, "w")

    #need to calc weight here
    out.write(str(tour[1]))

    # need to write the path for the above length here
    out.write(str(tour[0]))



if __name__ == "__main__":
    main()