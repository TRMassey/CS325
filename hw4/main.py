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
def nearest_int(num):
    if num-int(num) >= .5:
        return int(num)+1
    else:
        return int(num) 



# Description: takes given list and calculates edges to/from 
# all v
# Parmeters: Graph in format from func makeGraph()
# Return: dict of key=(vertex#,vertex#), value = edge weight 
def graph_edges(G):
    lowRange = 0
    edges  = dict()
    #iterate through all start points
    for vertex1 in range(0, len(G)):
        lowRange += 1
        #iterate through all end points
        for vertex2 in [x for x in xrange(len(G)) if x != vertex1]:
            #this is from assignment description
            edges[(vertex1,vertex2)] = nearest_int(math.sqrt(pow(G[vertex1][0]-G[vertex2][0], 2)+pow(G[vertex1][1]-G[vertex2][1],2)))
    #dict of key=(vertex#,vertex#), value = edge weight 
    return edges



# Description:  Prims algorithm for min spanning tree.  Only works
# for TSP problems, where all vertices connect to all other vertices.
# Parmeters: Graph in format from func makeGraph()
# Return: a list of edges in min spanning tree ex: [(0,1),(1,2),(3,4)]
def mst_prim(G):
    #set edges in dict (start, end) = weight
    edges = graph_edges(G)
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
    print degrees
    for v in degrees.keys():
        if degrees[v] & 1:
            odd.append(v)
    #returns list of vertices with odd degrees
    return odd



# def minPerf(O, G):


# def multiGraph(T, M):


# def ecircuit(H):


# def hamcircuit(E):


# def tsp_christofides(G):
def tsp_christofides(G):
    #T = mst_prim(G, w, r)
    #O = oddDegrees(T)
    #M = MinWeightPerfMatch(O, G)
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