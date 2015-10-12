#include "algorithms.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <cstring>

int main(){

	std::ifstream input;									// file pointer
	std::ostream output;									// file pointer
	std::vector<std::string> intialRead;		// read into this vector, vector of vectors
	std::vector<std::vector<int>> converted;				// read vector convereted to integers
	std::vector<std::string> line;
	int result;

	// read the file
	input.open(filenamehere);
		// make sure we test for errors


	// store file contents in a vector
	while(!input.eof()){
		input >> line;
		initialRead.push_back(line);
	}

	// close
	input.close();


	// open the file for writing
	output.open(filenamehere);
		// test for errros


	// write each line and the result from the algo
	for(int i=0; i < initialRead.size; i++){
		output << intialRead[i];								// write the line
		output << "\n";											// spacing
		converted = intialRead[i] converted into ints. Maybe another function?
		result = algorithm1(converted);							// call the function
		output << result;										// write the answer
		output << "\n\n";										// spacing
	}

	// repeat for other three functions

close writing
	return 0;
}