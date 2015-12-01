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
def mstPrim(edges, G):
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
    minPerf = dict()
    #iterate through vertices in O
    for vertex in O:
        curMin = float("inf")
        #find shortest path from O[i] to other vertex in O
        for data in edges.keys():
            #if less than curMin, make new curMin
            if(data[0] == vertex):
                #find edge connecting to other v in O
                if(data[1] in O):
                    if(edges[data] < curMin):
                        curMin = edges[data]
                        curEdge = data
            elif(data[1] == vertex):
                #find edge connecting to other v in O
                if(data[0] in O):
                    if(edges[data] < curMin):
                        curMin = edges[data]
                        curEdge = data
        #add path
        minPerf[curEdge] = curMin
    #get rid of any duplicate vertices
    
    return minPerf


# Description: Takes mst and edges from min perf and combines 
# them into one graph/edge list representation
# Parameters: mst edge list,  edge list of min weight perfect 
# matching
# Return: dictionary (city1, city2) = weight
def multiGraph(T, M, edges):
    for edge in T:
        if edge not in M.keys():
            M[edge] = edges[edge]
    return M




# Description: Takes edge list and runs/finds Euler Circuit
# Parameters: dict from multigraph combo of minPerf and 
# mstPrim (city1, city2) = weight
# Return: list of cities in euler
# Citation: https://github.com/plawanrath/AI_Euler_Paths-Cycles/blob/master/paths_graph1.py 
#Citation: https://github.com/sbebo/graph/blob/master/tsp.py

def eCircuit(H):
    edges = len(H)
    degrees = {}
    oddN = 0

    # determine degrees
    for edge in H:
        for node in edge:
          if node in degrees:
                degrees[node] += 1
          else:
                degrees[node] = 1

    # determine which have an odd degree
    for node in degrees:
        if degrees[node] % 2 == 1:
            oddN += 1

    # To have a Euler Circuit, number of nodes w/odd degree must be 0 or 2
    if oddN !=2:
        if oddN != 0:
            return None

    #  make new path, it's still a dictionary
    newH = H
    tour = {}

    #  must start with odd node when applicable
    for node in degrees:
        if degrees[node] % 2 == 1:
            startNode = newH[node]
            break
        else:
            startNode = newH.iterkeys().next()

    # find subtours starting at the starting node
    tour = [startNode]
    for node in degrees:
        tour = [-1]
 
    # find subtours starting at the starting node
    stack = [startNode]
    while stack:
        vertex = stack[-1]
        foundEdge = False
        #search for edge using starting point vertex
        for edges in H.keys():
            if vertex == edges[0]:
                destination = edges[1]
                stack.append(destination)
                #remove from dict so not reused
                H.pop(edges)
                foundEdge = True
                break
        if not foundEdge:
            #this enters list backwards, will need to reverse start+1 to end-1
            vertex = stack.pop()
            tour.append(vertex)
    #clean up, reverse start-1 to end-1
    tour[1:len(tour)-1] = reversed(tour[1:len(tour)-1])

    return tour



# Description: Takes Euler Circuit and runs/finds Hamiltonian
# Cycle/Circuit
# Parameters: Euler circuit as list of vertices
# Return: Hamiltonian circuit as list of vertices
# Citation: https://github.com/sbebo/graph/blob/master/tsp.py
def hamCircuit(E):
    #to become ham, cut circle (start and end should be same node from Euler)
    if(E[0] == E[len(E)-1]):
        E.pop()
    
    #DFS on one tour
    visitedNodes = dict((vertex, False) for vertex in E)
    index = 0
    stack = [E[index]]
    hamilton = []

    while len(stack) > 0:
        vertex = stack.pop()
        #valid if not visited yet, add to path
        if visitedNodes[vertex] == False:
            visitedNodes[vertex] = True
            hamilton.append(vertex)
            #if neighbor, add to stack
            if(index+1 < len(E)):
                index += 1
                stack.append(E[index])

    return hamilton



# def tsp_christofides(G):
def tsp_christofides(G):
    #edges = graphEdges(G)
    #T = mstPrim(edges, G)
    #O = oddDegrees(T)
    #M = minPerf(O, edges)
    #H = multiGraph(T, M, edges)
    #E = eCircuit(v1 of H)
    #return hamCircuit(E)
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