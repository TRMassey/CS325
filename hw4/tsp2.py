'''
 Alt version to main.py
'''
import sys
import os
import math
import time


#route must be an array of some kind, i is start, j is end
# removing edges and reconnecting
#http://www.technical-recipes.com/2012/applying-c-implementations-of-2-opt-to-travelling-salesman-problems/
# OUT OF BOUNDS ERROR!!!! GRRRRRR!!!!!!!
def twoOptSwap(route, i, j): 
	newRoute = [None]*len(route)

	# take Route[0] to route[i-1] and put in new route
	for k in range(0, i):
		newRoute[k] = route[k][0]
		#print "K: ", k

	# take route[i] to route[j] and add then in reverse order
	dec = 0
	for k in range(i, j+1):
		newRoute[k] = route[j-dec][0]		# going out of bounds!?
		dec += 1

	# take route[j+1] to the end, and add them in order to a new route
	for k in range(j+1, len(route)):
		#print "K in 3: ", k
		newRoute[k] = route[k][0]

	return newRoute


#http://www.technical-recipes.com/2012/applying-c-implementations-of-2-opt-to-travelling-salesman-problems/
def optimize(graph, route, currentDistance):

	size = len(route)
	improve = 0

	while (improve < 20):
		bestDistance = currentDistance
		
		for i in range(0, len(route) - 1):

			for j in range(i + 1, len(route)):

				#reverse and swap per wikipedia, removing edge
				new_route = twoOptSwap(route, i, j)
				new_distance = new_route[0]		# OUT OF RANGE!?

				if new_distance < bestDistance:
					#improvement found
					improve = 0
					bestDistance = new_distance
					route = new_route

				if bestDistance == currentDistance:
					break
		improve += 1

	return (route[0][0], bestDistance)


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
			if curVert != vert:
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
	#path.sort(key=lambda tup:tup[1])
### not sure about above parameters, need to lookup
	distance = optimize(G, path, path[0][1])

	return distance



def main():
    # Your program must:
    # Accept problem instances on the command line
    if len(sys.argv) != 2:
    	print "Error."
    	exit()

    f = open(sys.argv[1], "r")
    inputname = sys.argv[1]
    G = makeGraph()
    #print G
    f.close()   

	# timer needed
    start = time.time()
    # this is where we would call the algorithm
    tour = tsp(G)

    end = time.time()

    print "Time elapsed:",(end - start), "seconds"

    print "Tour length:", tour[1]
	
    formatting = list()
	
    formatting = tour[0]

    # Name the output file as the input file's name with .tour appended 
    outputname = inputname + ".tour"

    out = open(outputname, "w")

    #need to calc weight here
    out.write(str(tour[1]))
    out.write('\n')

    # need to write the path for the above length here
    for f in formatting:
	    out.write(str(f) + '\n')


if __name__ == "__main__":
    main()