# Project 4
# Project group 1
# Lynn Herrick, Tara Massey, Diana O'Haver

import sys
import time

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

# def mst_prim(G, w, r):


# def oddDegrees(T):


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