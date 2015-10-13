#include "algorithms.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <cstring>

int main(int argc, char* argv[]){

	std::ifstream input;									// file pointer
	std::ostream output;									// file pointer
	std::vector<std::string> intialRead;					// read into this vector, vector of vectors
	std::vector<std::vector<int>> converted;				// read vector convereted to integers
	std::vector<std::string> line;
	std::string fileName;									// name of file to be read
	int result;


// Step One: Address possible conditions for selecting proper user input

	// if a filename is provided
	if(argc == 2){
		fileName = argv[1];;
	}
	else{
		fileName = "MSS_Problems.txt";
	}

// Step Two: Open the file and address errors conccerning bad user input
	input.open(fileName);
	if(!input.is_open()){
		std::cout << "ERROR: file unable to be opened\n";
		return 0;
	}


// Step Three: Store the file contents in a vector for use
	while(std::getline(input, line)){
		input >> line;
		initialRead.push_back(line);		// each line of input stores to one element in the vector
	}


// Step Four: Close and deal with closing errors
	input.close();
	if(input.is_open()){
		std::cout << "ERROR: file unable to be properly closed\n";
	}


// Step Five: Open the file for writing and deal with opening errors
	fileName = "MSS_Results.txt";			// changed for output file
	output.open(fileName);
	if(!output.is_open()){
		std::cout << "ERROR: file unable to be opened for writing"
	}


// Step Six: The file contents stored in a vector will be otuput to the
// result file, then the line will be converted to only integers, the
// algorithm will run on the converted line, return a result, and the result
// will be written to the same output file.
	for(int i=0; i < initialRead.size; i++){
		output << intialRead[i];								// write the line
		output << "\n";											// spacing

		// NEED TO TOKENIZE AND CONVERT WITH ATOI ONCE COMMAS, SPACES, and BRACES ARE GONE
		converted = intialRead[i] converted into ints. Maybe another function?

		result = algorithm1(converted);							// call the function
		output << result;										// write the answer
		output << "\n\n";										// spacing
	}

	// repeat for other three functions

// Step Last: Close and deal with closing errors
	output.close();
	if(output.is_open()){
		std::cout << "ERROR: file unable to be properly closed\n";
	}

	return 0;
}

