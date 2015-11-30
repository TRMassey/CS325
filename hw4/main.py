# Project 4
# Project group 1
# Lynn Herrick, Tara Massey, Diana O'Haver

import sys
import time
import math

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
            edges[(vertex1,vertex2)] = nearestInt(math.sqrt(pow(G[vertex1][0]-G[vertex2][0], 2)+pow(G[vertex1][1]-G[vertex2][1],2)))
    #dict of key=(vertex#,vertex#), value = edge weight 
    return edges



# Description:  Prims algorithm for min spanning tree.  Only works
# for TSP problems, where all vertices connect to all other vertices.
# Parmeters: set edges in dict (start, end) = weight
# Return: a list of edges in min spanning tree ex: [(0,1),(1,2),(3,4)]
def mstPrim(edges):
    A = list() # A = {(v, v.pie): v in V-{r}-

    #each key is set to infinity
    key = [float("inf")]*len(G)
    #each parent is set to null
    parent = [None]*len(G)

    #tset root/starting point
    cur = 0
    key[cur] = 0
    #Q is a list of all vertices
    Q = list()
    for v in range(0, len(G)):
        Q.append(v)
    minList = [None]*len(Q) #this will be used later to go between Q and key
    Qsize = len(Q)
    #while Q is not empty
    while Q:
        #find smallest key of applicble Qs
        minList = [float("inf")]*Qsize
        for num in Q:
            minList[num] = key[num]
        u = min(u for u in minList)
        #remove Q that was used
        cur = (key.index(u))
        Q.remove(cur)

        if parent[cur] != None:
            A.append((parent[cur], cur))

        #in this assignment, all verts are neighbors
        for neighbor in [x for x in xrange(len(G)) if x != cur]:
            #print edges[(cur,neighbor)]
            if neighbor in Q and edges[(cur,neighbor)] < key[neighbor]:
                parent[neighbor] = cur
                key[neighbor] = edges[(cur,neighbor)]
    return A



# Description: seperates out vertices from edge list, counts how
# many edges/degrees each vertex has, returns vertices with odd 
# degress
# Parmeters: List of edges ex: [(0,1),(1,2),(3,4)]
# Return: list of vertices with odd degrees ex: [1,2,3] 
def oddDegrees(T):
    degrees = dict()
    odd = list()
    for x in range(0, len(T)*2):
        degrees[x] = 0
    #degrees are the amount of edges that conenct to v
    for edge in T:
        degrees[edge[0]] += 1
        degrees[edge[1]] += 1
    for v in degrees.keys():
        if degrees[v] & 1:
            odd.append(v)
    #returns list of vertices with odd degrees
    return odd



# Description: Finds min weight perfect match from mst vs full
# graph
# Parameters: odd degree vertex list, dict of full graph's edges
# with weight
# Return: min weight perfect matching edge list
def minPerf(O, edges):
    #take vertices from O and find those edges in edges
    combinedGraph = dict()
    deadEnds = dict()
    for path in edges:
        #if both vertices in O, path as is
        if path[1] in O and path[2] in O:
            combined[path] = edges[path]
        #if only one vertex in O, add until other vertex (add until not dead end)
        elif path[1] in O or path[2] in O:
            pass #stuck here :(

    # find/return the min edges so all vertices are touched
    pass


# Description: Takes mst and edges from min perf and combines 
# them into one graph/edge list representation
# Parameters: mst edge list,  edge list of min weight perfect 
# matching
# Return: 
def multiGraph(T, M):
    pass



# Description: Takes edge list and runs/finds Euler Circuit
# Parameters: edge list from multigraph combo of minPerf and 
# mstPrim
# Return: 
def ecircuit(H):
    pass



# Description: Takes Euler Circuit and runs/finds Hamiltonian
# Cycle/Circuit
# Parameters: 
# Return: 
def hamCircuit(E):
    pass



# def tsp_christofides(G):
def tsp_christofides(G):
    #edges = graphEdges(G)
    #T = mstPrim(edges)
    #O = oddDegrees(T)
    #M = MinWeightPerfMatch(O, edges)
    #H = MultiGraph(T, M)
    #E = ECircuit(v1 of H)
    #return HamCircuit(E)
    pass



def main():
    # Your program must:
    # Accept problem instances on the command line
    f = open(sys.argv[1], "r")
    inputname = sys.argv[1]
    G = makeGraph()
    print G
    f.close()   

	# timer needed
    start = time.time()
    # this is where we would call the algorithm
    tour = "algorithm here"

    end = time.time()

    print "Time elapsed:",(end - start), "seconds"

    print "Tour length:", tour

    # Name the output file as the input file's name with .tour appended 
    outputname = inputname + ".tour"

    out = open(outputname, "w")

    out.write(tour)

    # need to write the path for the above length here





if __name__ == "__main__":
    main()