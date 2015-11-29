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

	#repeat until no improvement is made
    while True:
        bestDistance = currentDistance
        for i in range(1, len(route) - 1):
            for j in range(i + 1, len(route)):

            	#positions
            	one = i;
            	two = i+1 % len(route)
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
                    # NOTE: This mmay need to be pulled out of the if statement, as it's listed that way in wikipedia
                    new_route = twoOptSwap(route, i + 1, j)

               		if new_distance < bestDistance:
                    	bestDistance = new_distance

       				if bestDistance == currentDist:
           				 break

    return bestDistance