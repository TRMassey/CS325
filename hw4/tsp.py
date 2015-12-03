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
    
    #this reverses the list only from i to j
    route[i:j] = route[i:j][::-1]
    return route
    '''
    for k in range(i, len(route)):
        routeTwo[counter] = route[k]
        newRoute(reversed(routeTwo))
    return newRoute
    '''


def optimize(graph, route, currentDistance, edges):
    bestDistance = currentDistance[1]
    new_route = route[0]

    for i in range(0, len(route)):  #since files start at 0, len(route) ok
        #positions
        one = i;
        two = (i+1) % len(route)

        j = i+2
        while (j+1)%len(route) != i:

            three = j % len(route)
            four = (j+1) % len(route)

            #determine shortest
            if ((edges[one, three] + edges[two, four]) < (edges[one, two] + edges[three, four])):
                new_distance = currentDistance[1]
                new_distance -= (edges[one, two] + edges[three, four] - edges[one, three] - edges[two, four])
                #reverse and swap per wikipedia, removing edge
                new_route = twoOptSwap(route[0][0], i+1, j)

                if new_distance < bestDistance:
                    bestDistance = new_distance

                if bestDistance == currentDistance:
                    break
            j += 1

    return new_route, bestDistance



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
    edges  = dict()
    #iterate through all start points
    for vertex1 in range(0, len(G)):
        #iterate through all end points
        for vertex2 in [x for x in xrange(len(G)) if x != vertex1]:
            #this is from assignment description
            edges[(int(vertex1),int(vertex2))] = nearestInt(math.sqrt(((int(G[vertex1][0])-int(G[vertex2][0]))**2)+((int(G[vertex1][1])-int(G[vertex2][1]))**2)))
    #dict of key=(vertex#,vertex#), value = edge weight 
    return edges



def greedyPath(vertex, vertices, edges):
    curVert = vertex # current vertex being considered
    minEdge = float("inf") #compare mins when iterating
    minVert = None  #compare mins when iterating
    path = list() # list of decided path for tsp
    distance = 0    #combined distance of final path
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
    for vertex in range (0, len(G)):
        vertices.append(vertex)

    for vertex in vertices:
        path.append(greedyPath(vertex, vertices, edges))

    #get the optimal path in first index
    path.sort(key=lambda tup:tup[1])        #if greedy only

    #distance = optimize(G, path, path[0], edges)   #if opt-2

    return path[0]  #if greedy only
    #return distance  #if opt-2



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