#include "algorithms.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <time.h>

int main(){

	std::ifstream input;									// Input Stream
	std::ofstream output;									// Output Stream
	std::vector<std::string> initialRead;					// read into this vector, vector of vectors
	std::vector<std::vector<int> > converted;				// read vector convereted to integers
	std::string line;										// string for easier iteration through vector of strings
	std::string fileName;									// name of file to be read or written to
	int result;												// algorithm's answer


	srand(time(NULL));										// set for random generation
	

// Step Two: Open the file and address errors conccerning bad user input
	input.open("MSS_Problems.txt");
	if(!input.is_open()){
		std::cout << "ERROR: file unable to be opened\n";
		return 0;
	}


// Step Three: Store the file contents in a vector for use
	while(std::getline(input, line)){
		initialRead.push_back(line);		// each line of input stores to one element in the vector
	}


// Step Four: Close and deal with closing errors
	input.close();
	if(input.is_open()){
		std::cout << "ERROR: file unable to be properly closed\n";
	}


// Step Five: Open the file for writing and deal with opening errors
	output.open("MSS_Results.txt");
	if(!output.is_open()){
		std::cout << "ERROR: file unable to be opened for writing";
	}


// Step Six: The file contents stored in a vector will be otuput to the
// result file, then the line will be converted to only integers, the
// algorithm will run on the converted line, return a result, and the result
// will be written to the same output file.

	// algorithm One
	std::cout << "\nRunning Analysis from file on Algorithm One";
	for(int i=0; i < initialRead.size; i++){
		output << intialRead[i];								// write the line
		output << "\n";											// spacing

		// Begin tokenization
		line = initialRead[i];		// for easier iteration
		std::string newLine;		// string without brackets

		// strip brackets. New array made without brackets in newLine.
		int k = 0;
		for(int j=0; j < line.length(); j++){
			if(line[j] == '[' || line[j] == ']'){
				continue;
			}
			else{
				newLine[k] = line[j];
				k++;
			}
		}

		// tokenize based off commas
		char* toTokenize = line.c_str();
		char* token = strtok((char*) toTokenize, ",");
		while(token != NULL){
			int temp = atoi(token);
			converted.push_back(temp);
			token = strtok(NULL, ",");
		}
		
		result = algorithm1(converted);							// call the function
		output << result;										// write the answer
		output << "\n\n";										// spacing
	}
	std::cout << "\nFile contents written.\n";


	
	// Algorithm two
	std::cout << "\nRunning analysis of file on Algorithm Two";
	for(int i=0; i < initialRead.size; i++){
		output << intialRead[i];								// write the line
		output << "\n";											// spacing

		// Begin tokenization
		line = initialRead[i];		// for easier iteration
		std::string newLine;		// string without brackets

		// strip brackets. New array made without brackets in newLine.
		int k = 0;
		for(int j =0; j < line.size(); j++){
			if(line[j] == '[' || line[j] == ']'){
				continue;
			}
			else{
				newLine[k] = line[j];
				k++;
			}
		}

		// tokenize based off commas
		char* toTokenize = line.c_str();
		char* token = strtok((char*) toTokenize, ",");
		while(token != NULL){
			int temp = atoi(token);
			converted.push_back(temp);
			token = strtok(NULL, ",");
		}
		
		result = algorithm2(converted);							// call the function
		output << result;										// write the answer
		output << "\n\n";										// spacing
	}
	std::cout << "\nFile contents written.\n";

	// algorithm Three
	std::cout << "\nRunning Analysis on file for Algorithm Three";
	for(i=0; i < initialRead.size; i++){
		output << intialRead[i];								// write the line
		output << "\n";											// spacing

		// Begin tokenization
		line = initialRead[i];		// for easier iteration
		std::string newLine;		// string without brackets

		// strip brackets. New array made without brackets in newLine.
		int k = 0;
		for(int j=0; j < line.size(); j++){
			if(line[j] == '[' || line[j] == ']'){
				continue;
			}
			else{
				newLine[k] = line[j];
				k++;
			}
		}

		// tokenize based off commas
		char* toTokenize = line.c_str();
		char* token = strtok((char*) toTokenize, ",");
		while(token != NULL){
			int temp = atoi(token);
			converted.push_back(temp);
			token = strtok(NULL, ",");
		}
		
		result = algorithm3(converted, 0, converted.size()-1);	// call the function
		output << result;										// write the answer
		output << "\n\n";										// spacing
	}
	std::cout << "\nFile contents written\n";


	// algorithm Four
	std::cout << "\nRunning Analysis on File for Algorithm Four";
	for(int i=0; i < initialRead.size; i++){
		output << intialRead[i];								// write the line
		output << "\n";											// spacing

		// Begin tokenization
		line = initialRead[i];		// for easier iteration
		std::string newLine;		// string without brackets

		// strip brackets. New array made without brackets in newLine.
		int k = 0;
		for(int j=0; j < line.size(); j++){
			if(line[j] == '[' || line[j] == ']'){
				continue;
			}
			else{
				newLine[k] = line[j];
				k++;
			}
		}

		// tokenize based off commas
		char* toTokenize = line.c_str();
		char* token = strtok((char*) toTokenize, ",");
		while(token != NULL){
			int temp = atoi(token);
			converted.push_back(temp);
			token = strtok(NULL, ",");
		}
		
		result = algorithm4(converted);							// call the function
		output << result;										// write the answer
		output << "\n\n";										// spacing
	}
	std::cout << "\nFile contents written\n";

// Step Seven: Close and deal with closing errors
	output.close();
	if(output.is_open()){
		std::cout << "ERROR: file unable to be properly closed\n";
	}


// PART TWO : Timing with random number generator
	std::cout << "\n TIMING ANALYSIS BEGINNING FOR n AMOUNT OF RANDOM VALUES:";
	std::vector<int> nArray = {100, 200, 400, 600, 900, 1000, 2000};	// sizes of array
	std::vector<int> random;
	double t1, t2;

	// will run for as long as we have numbers of n input
	for(i=0; i < nArray.size(); i++){

		// we will run each n input size 10 times
		for(int k=0; k < 10; k++){

			// make the array of n inputs, all random numbers
			for(int j=0; j < nArray[i]; j++){
				random[j] = rand() % nArray.size() + 1;
			}

			// run each of the algorithms
			std::cout << "Algorithm1:\n";
			t1 = 1000 * clock() / CLOCKS_PER_SEC;
			result = algorithm1(random);
			t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
			std::cout << "\nRUNTIME FOR SIZE ";
			std::cout << nArray[i];
        	std::cout << " - Running time for Algorithm1 is: ";
        	std::cout << result;
        	std::cout << "\n";

        			
			std::cout << "Algorithm2:\n";
			t1 = 1000 * clock() / CLOCKS_PER_SEC;
			result = algorithm2(random);
			t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
			std::cout << "\nRUNTIME FOR SIZE ";
			std::cout << nArray[i];
        	std::cout << " - Running time for Algorithm1 is: ";
        	std::cout << result;
        	std::cout << "\n";

        		
			std::cout << "Algorithm3:\n";
			t1 = 1000 * clock() / CLOCKS_PER_SEC;
			result = algorithm3(random, 0, random.size()-1);
			t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
			std::cout << "\nRUNTIME FOR SIZE ";
			std::cout << nArray[i];
        	std::cout << " - Running time for Algorithm1 is: ";
        	std::cout << result;
        	std::cout << "\n";

			std::cout << "Algorithm4:\n";
			t1 = 1000 * clock() / CLOCKS_PER_SEC;
			result = algorithm4(random);
			t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
			std::cout << "\nRUNTIME FOR SIZE ";
			std::cout << nArray[i];
        	std::cout << " - Running time for Algorithm1 is: ";
        	std::cout << result;
        	std::cout << "\n";
        }
	}
	return 0;
}

