import sys
import os
import math
import time
import operator


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



def calcEdge(x,y):
    return nearestInt(math.sqrt(((int(x[0])-int(y[0]))**2)+((int(x[1])-int(y[1]))**2)))



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
            #edges[(int(vertex1),int(vertex2))] = nearestInt(math.sqrt(((int(G[vertex1][0])-int(G[vertex2][0]))**2)+((int(G[vertex1][1])-int(G[vertex2][1]))**2)))
            edges[(int(vertex1),int(vertex2))] = calcEdge(G[vertex1], G[vertex2])
    #dict of key=(vertex#,vertex#), value = edge weight 
    return edges




def totalDistance(path, edges):
    distance = 0
    curVert = path[0]
    #iterate through list starting at index 1 (index 0 is distance of 0):
    for vertex in path [2:]:
        distance += edges[curVert, vertex]
        curVert = vertex
    distance += edges[curVert, path[0]]
    return distance



# Description:  Prims algorithm for min spanning tree.  Only works
# for TSP problems, where all vertices connect to all other vertices.
# Parmeters: set edges in dict (start, end) = weight
# Return: a list of edges in min spanning tree ex: [(0,1),(1,2),(3,4)]
def mstPrim(edges, G):
    vertList = list()
    edgeList = list()

    #create list of vertices
    Q = list()
    for vertex in range(0, len(G)):
        Q.append(vertex)

    #each key is set to infinity
    key = [float("inf")]*len(G)
    #each parent is set to null
    parent = [None]*len(G)

#   Qsize = len(Q)
#    minList = [None]*len(Q) #this will be used later to go between Q and key

    #tset root/starting point
    cur = 0
    key[cur] = 0
    vertList.append(Q[0]) #start at 0
    Q.remove(Q[0])

    #while Q is not empty
    while Q:
        minV1 = float("inf")
        minV2 = float("inf")
        minEdge = float("inf")
        #find smallest key of applicble Qs, edges are pre-sorted
        for vertex in vertList:
            for edge in edges:
                #start is vertex
                if edge[0][0] == vertex:
                    if edge[0][1] in Q:
                        minEdge = edges[1]
                        minV1 = vertex
                        minV2 = edge[0][1]
                        break # found has to be solution
                #destination is vertex
                elif edge[0][1] == vertex:
                    if edge[0][0] in Q:
                        minEdge = edges[1]
                        minV1 = edge[0][1]
                        minV2 = edge[0][0]
                        break #found has to be solution
        vertList.append(minV2)
        Q.remove(minV2)
        edgeList.append((minV1,minV2))
    return (vertList, edgeList)


#uses 2-opt
def buildPath(vertices, vertPath, edges):
    #go through the path or mst backwards
    for vertex in range(len(vertPath) -3):
        order1 = 0
        order2 = 0
        #2-opt rule: swap if [1,3,2,4] < [1,2,3,4]
        order1 = edges[vertex, vertex+2]+edges[vertex+2, vertex+1]+edges[vertex+1, vertex+3]
        order2 = edges[vertex, vertex+1]+edges[vertex+1, vertex+2]+edges[vertex+2, vertex+3]
        if(order1 < order2): #2-opt swap
        	#swap 2 and 3
        	temp = vertPath[vertex+1]
        	vertPath[vertex+1] = vertPath[vertex+2]
        	vertPath[vertex+2] = temp
    return vertPath





def tsp(G):
    #get list of vertices
    vertices = list()
    for vertex in range(0, len(G)):
        vertices.append(vertex)

    #get edges for graph
    edges = graphEdges(G)
    #sort dictionary by values/edges
    tempEdges = sorted(edges.items(), key=lambda x: x[1])

    #make prims mst
    mst = mstPrim(tempEdges, G)
    vertPath = mst[0]   #vert in order from mst
    edgePath = mst[1]   #edges in order from mst

    #find path
    #establish current distance after mst
    distance = 0
    for edge in edgePath:
        distance += edges[edge]

    #establish exact min path
    minPathFound = False
    while not minPathFound:
        #build path
        vertPath = buildPath(vertices, vertPath, edges)
        curVerts = []
        curDist = 0
        #check if better
        if curDist < distance:
            distance = curDist
            vertPath = curVerts
        #min has been found
        else:
            minPathFound = True

    return results




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
    #distance = optimize(G, tour, tour[1])

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