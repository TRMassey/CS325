import sys
import math

# To avoid floating point precision problems in computing the squareroot,
# we will always round the distance to the nearest integer 
def nearest_int(num):
	if num-int(num) >= .5:
		return int(num)+1
	else:
		return int(num) 


# takes given list and calculates edges to/from all v
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
	minList = [None]*len(Q)	#this will be used later to go between Q and key
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


'''
# Simple test from assignment description for graph_edges and nearest_int
# should output {(0,1): 3, (1,2): 6, (0,2): 6}
G = ((0,0), (1,3), (6,0))
print graph_edges(G)
'''
'''
# tests for mst_prim go here
# should output [(0,1),(0,2)]
G = ((0,0), (1,3), (6,0))
print mst_prim(G)
#print "\n"
G = ((200,800), (3600,2300), (3100,3300), (4700,5750), (5400,5750), (5608,7103))
#print graph_edges(G)
#{(1, 3): 3621, (3, 0): 6690, (5, 4): 1369, (2, 1): 1118, (5, 1): 5206, (2, 5): 4556, (0, 3): 6690, (4, 0): 7179, (1, 2): 1118, (1, 5): 5206, (5, 0): 8305, (0, 4): 7179, (5, 3): 1629, (4, 1): 3891, (3, 2): 2926, (4, 5): 1369, (1, 4): 3891, (0, 5): 8305, (4, 2): 3360, (1, 0): 3716, (3, 5): 1629, (0, 1): 3716, (5, 2): 4556, (3, 1): 3621, (0, 2): 3829, (2, 0): 3829, (4, 3): 700, (2, 3): 2926, (3, 4): 700, (2, 4): 3360}
# expected output [(0,1),(1,2),(2,3),(3,4),(4,5)]
print mst_prim(G)
'''

edges = {(0,1): 3, (1,2): 6, (0,2): 6}
O = [1,2]

def minPerf(O, edges):
    #take vertices from O and find those edges in edges
    combinedGraph = list()
    for path in edges:
        if path[1] in O or path[2] in O:
        	combined[path] = edges[path]

minPerf(O, edges)