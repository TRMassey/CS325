# Project 4
# Project group 1
# Lynn Herrick, Tara Massey, Diana O'Haver

import sys
import time

# Your program must:
# Accept problem instances on the command line

f = open(sys.argv[1], "r")
inputname = sys.argv[1]
contents = f.read()
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

