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
		for vertex2 in range(lowRange, len(G)):
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
	#while Q is not empty
	while Q:
		#find smallest key of applicble Qs
		minList = [None]*len(minList)
		for num in Q:
			if key[num]:
				minList[num] = key[num]
			else:
				minList[num] = float("inf")
		u = min(u for u in minList)
		#remove Q that was used
		cur = (key.index(u))
		Q.pop(cur)

		if parent[cur] != None:
			A.push(cur, parent[cur])

		#in this assignment, all verts are neighbors
		for neighbor in [x for x in xrange(len(G)) if x != cur]:
			#print edges[(cur,neighbor)]
			if neighbor in Q and edges[(cur,neighbor)] < key[neighbor]:
				parent[neighbor] = cur
				key[neighbor] = edges[(cur,neighbor)]
	return A


G = ((0,0), (1,3), (6,0))
print mst_prim(G)

'''
# Simple test from assignment description for graph_edges and nearest_int
# should output {(0,1): 3, (1,2): 6, (0,2): 6}
G = ((0,0), (1,3), (6,0))
print graph_edges(G)
'''


