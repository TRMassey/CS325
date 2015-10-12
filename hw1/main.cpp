#include "algorithms.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <cstring>

int main(){

	std::ifstream fp;					// file pointer
	std::vector<string> intialRead;		// read into this vector
	std::vector<int> converted;			// read vector convereted to integers
	std::vector<int> resultsInt;			// pass empty vector, return full of results
	std::vector<string> finalResult;		// info about algo and ints as strings for final read

	// Step One: Open and read the file
		// remember error catch if problem opening

		// read into vector

		// remember to close when done


	// Step Two: Convert vector of strings to ints
		// while the vectore isn't empty
			// use ataoi on the present element
			// push present element into the vector

	// Step Three: Send converted vector to Function One

		// Open the results file for writing!

		// send to function with int vector and empty vector
		// empty vector returns full
		// open result file
			// write into it the algo we're on
			// write into it the resultInt vector, converted to c.string
			// close
		// empty resultInt vector

		// Step Four: Send converted vector to Function Two
		// send to function with int vector and empty vector
		// empty vector returns full
		// open result file
			// write into it the algo we're on
			// write into it the resultInt vector, converted to c.string
			// close
		// empty resultInt vector

		// Step Five: Send converted vector to Function Three
		// send to function with int vector and empty vector
		// empty vector returns full
		// open result file
			// write into it the algo we're on
			// write into it the resultInt vector, converted to c.string
			// close
		// empty resultInt vector

		// Step Six: Send converted vector to Function Four
		// send to function with int vector and empty vector
		// empty vector returns full
		// open result file
			// write into it the algo we're on
			// write into it the resultInt vector, converted to c.string
			// close
		// empty resultInt vector

		// Close the results file!


	return 0;
}