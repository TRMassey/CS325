#include "algorithms.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <time.h>
#include <cstddef>
#include <iomanip>

int main(){

	std::ifstream input;									// Input Stream
	std::ofstream output;									// Output Stream
	std::vector<std::string> initialRead;					// read into this vector, vector of vectors
	std::vector<int> converted;								// read vector convereted to integers
	std::string line;										// string for easier iteration through vector of strings
	std::string fileName;									// name of file to be read or written to
	int result;												// algorithm's answer
	float total;												// total runtime
	std::string choice;


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

	for(int i=0; i < initialRead.size(); i++){
		output << "\nArray Processed :  ";
		output << initialRead[i];								// write the line
		output << "\n\n";										// spacing

		// Begin tokenization
		line = initialRead[i];		// for easier iteration

        // replace all non-spaces with spaces
        std::size_t found = line.find_first_of("[,]");

        while (found!=std::string::npos) {
            line[found]=' ';
            found=line.find_first_of("[,]",found+1);
        }

        // tokenize based off spaces
		const char* toTokenize = line.c_str();
		char* token = strtok((char*) toTokenize, " ");
		converted.clear();
		while(token != NULL){
			int temp = atoi(token);
			converted.push_back(temp);
			token = strtok(NULL, " ");
		}

		result = algorithm1(converted);
		// call the function
		std::cout << "\nResult is " << result;
		output << "Algorithm One Result : ";
		output << result;										// write the answer
		output << "\n";										// spacing

	}
	std::cout << "\nFile contents written.\n";

		// Algorithm two
	std::cout << "\nRunning analysis of file on Algorithm Two";
	for(int i=0; i < initialRead.size(); i++){
		output << "Array Processed :  ";
		output << initialRead[i];								// write the line
		output << "\n";											// spacing

		// Begin tokenization
		line = initialRead[i];		// for easier iteration

        // replace all non-spaces with spaces
        std::size_t found = line.find_first_of("[,]");

        while (found!=std::string::npos) {
            line[found]=' ';
            found=line.find_first_of("[,]",found+1);
        }

        // tokenize based off spaces
		const char* toTokenize = line.c_str();
		char* token = strtok((char*) toTokenize, " ");
		converted.clear();
		while(token != NULL){
			int temp = atoi(token);
			converted.push_back(temp);
			token = strtok(NULL, " ");
		}



		result = algorithm2(converted);							// call the function
        std::cout << "\nResult is " << result;
		output << "Algorithm Two Result : ";
		output << result;										// write the answer
		output << "\n\n";										// spacing


	}

	std::cout << "\nFile contents written.\n";



	// algorithm Three
	std::cout << "\nRunning Analysis on file for Algorithm Three";
	for(int i=0; i < initialRead.size(); i++){
		output << "Array Processed :  ";
		output << initialRead[i];								// write the line
		output << "\n";											// spacing

		// Begin tokenization
		line = initialRead[i];		// for easier iteration
		//std::cout << "\nline is " << line;
		//std::string newLine;		// string without brackets

        // replace all non-spaces with spaces
        std::size_t found = line.find_first_of("[,]");

        while (found!=std::string::npos) {
            line[found]=' ';
            found=line.find_first_of("[,]",found+1);
        }

        // tokenize based off spaces
		const char* toTokenize = line.c_str();
		char* token = strtok((char*) toTokenize, " ");
		converted.clear();
		while(token != NULL){
			int temp = atoi(token);
			converted.push_back(temp);
			token = strtok(NULL, " ");
		}



		result = algorithm3(converted, 0, converted.size()-1);	// call the function
        std::cout << "\nResult is " << result;
		output << "Algorithm Three Result : ";
		output << result;										// write the answer
		output << "\n\n";										// spacing

	}
	std::cout << "\nFile contents written\n";


	// algorithm Four
	std::cout << "\nRunning Analysis on File for Algorithm Four";
	for(int i=0; i < initialRead.size(); i++){
		output << "Array Processed :  ";
		output << initialRead[i];								// write the line
		output << "\n";											// spacing

		// Begin tokenization
		line = initialRead[i];		// for easier iteration
		//std::cout << "\nline is " << line;
		//std::string newLine;		// string without brackets

        // replace all non-spaces with spaces
        std::size_t found = line.find_first_of("[,]");

        while (found!=std::string::npos) {
            line[found]=' ';
            found=line.find_first_of("[,]",found+1);
        }

        // tokenize based off spaces
		const char* toTokenize = line.c_str();
		char* token = strtok((char*) toTokenize, " ");
		converted.clear();
		while(token != NULL){
			int temp = atoi(token);
			converted.push_back(temp);
			token = strtok(NULL, " ");
		}


		result = algorithm4(converted);
		std::cout << "\nResult is " << result;
		// call the function
		output << "Algorithm Four Result : ";
		output << result;										// write the answer
		output << "\n\n";										// spacing

	}
	std::cout << "\nFile contents written\n";



// Step Seven: Close and deal with closing errors
	output.close();
	if(output.is_open()){
		std::cout << "ERROR: file unable to be properly closed\n";
	}


// Ask the poor TA if they want to the run time analysis to go, or if they'd like to stop
	std::cout << "\n\nHave program run timing analysis for n inputs of each algorithm? (y or Y to continue): ";
	std::cin >> choice;
	if(choice != "y" && choice != "Y"){
		return 0;
	}

// PART TWO : Timing with random number generator
	std::cout << "\n TIMING ANALYSIS BEGINNING FOR n AMOUNT OF RANDOM VALUES:";
	std::vector<int> nArray;			// vector for storage and functions
	std::vector<int> random;
	float t1, t2;

	// fill the array with 100, 200, 300, 400, 500, 600, 700, 800, 900
	for(int i=100; i < 1000; i++){
		nArray.push_back(i);
		i = i + 99;
	}

	// add 1000, 2000, 3000, 4000, 5000 to array
	for(int i=1000; i < 6000; i++){
		nArray.push_back(i);
		i = i + 999;
	}


	// will run for as long as we have numbers of n input
	for(int i=0; i < nArray.size(); i++){
		int curSize = nArray[i];

		// we will run each n input size 10 times
		for(int k=0; k < 10; k++){

			// make the array of n inputs, all random numbers
			for(int j=0; j < curSize; j++){
				 random.push_back(rand() % curSize + 1);
			}
			
			// run each of the algorithms

			// handle small numbers, then bigger ones in the else
			if(i < 6){
				std::cout << "\nAlgorithm1:\n";
				t1 = 1000 * clock() / CLOCKS_PER_SEC;
				// loop numerous times to be able to get it up from 0
				for( int n = 0; n < 100; n++){
					result = algorithm1(random);
				}
				t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
				std::cout << "RUNTIME FOR SIZE ";
				std::cout << nArray[i];
        		std::cout << " - Running time for Algorithm1 is: ";
        		total = (t2-t1) / 100;	// divide answer by loops
        		std::cout << total;	
        		std::cout << "\n";


        		std::cout << "\nAlgorithm2:\n";
				t1 = 1000 * clock() / CLOCKS_PER_SEC;
				// loop numerous times to be able to get it up from 0
				for(int n = 0; n < 1000; n++){
					result = algorithm2(random);
				}
				t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
				std::cout << "RUNTIME FOR SIZE ";
				std::cout << nArray[i];
        		std::cout << " - Running time for Algorithm2 is: ";
        		total = (t2-t1) / 1000;	// divide answer by loops
        		std::cout << total;	
        		std::cout << "\n";


        		std::cout << "\nAlgorithm3:\n";
				t1 = 1000 * clock() / CLOCKS_PER_SEC;
				// loop numerous times to be able to get it up from 0
				for(int n = 0; n < 1000; n++){
					result = algorithm3(random, 0, random.size()-1);
				}
				t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
				std::cout << "RUNTIME FOR SIZE ";
				std::cout << nArray[i];
        		std::cout << " - Running time for Algorithm3 is: ";
        		total = (t2-t1) / 1000;	// divide answer by loops
        		std::cout << total;	
        		std::cout << "\n";


        		std::cout << "\nAlgorithm4:\n";
				t1 = 1000 * clock() / CLOCKS_PER_SEC;
				// loop numerous times to be able to get it up from 0
				for(int n = 0; n < 10000; n++){
					result = algorithm4(random);
				}
				t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
				std::cout << "RUNTIME FOR SIZE ";
				std::cout << nArray[i];
        		std::cout << " - Running time for Algorithm4 is: ";
        		total = (t2-t1) / 10000;	// divide answer by loops
        		std::cout << total;	
        		std::cout << "\n";
        	}

        	// larger numbers, no loops to increase decimal placement
        	else{
        		std::cout << "\nAlgorithm1:\n";
				t1 = 1000 * clock() / CLOCKS_PER_SEC;
				result = algorithm1(random);
				t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
				std::cout << "RUNTIME FOR SIZE ";
				std::cout << nArray[i];
        		std::cout << " - Running time for Algorithm1 is: ";
        		total = (t2-t1) / 10000;	// divide answer by loops
        		std::cout << total;	
        		std::cout << "\n";

     		   	std::cout << "\nAlgorithm2:\n";
				t1 = 1000 * clock() / CLOCKS_PER_SEC;
				result = algorithm2(random);
				t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
				std::cout << "RUNTIME FOR SIZE ";
				std::cout << nArray[i];
        		std::cout << " - Running time for Algorithm2 is: ";
        		total = (t2-t1);
        		std::cout << total;
        		std::cout << "\n";


				std::cout << "\nAlgorithm3:\n";
				t1 = 1000 * clock() / CLOCKS_PER_SEC;
				result = algorithm3(random, 0, random.size()-1);
				t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
				std::cout << "RUNTIME FOR SIZE ";
				std::cout << nArray[i];
        		std::cout << " - Running time for Algorithm3 is: ";
        		total = (t2-t1);
        		std::cout << total;
        		std::cout << "\n";

				std::cout << "\nAlgorithm4:\n";
				t1 = 1000 * clock() / CLOCKS_PER_SEC;
				result = algorithm4(random);
				t2 = 1000.0 * clock() / CLOCKS_PER_SEC;
				std::cout << "RUNTIME FOR SIZE ";
				std::cout << nArray[i];
        		std::cout << " - Running time for Algorithm4 is: ";
        		total = (t2-t1);
        		std::cout << total;
        		std::cout << "\n";
        	}
        	// clear vector
			for(int j=0; j < curSize; j++){
				 random.pop_back();
			}
        }
    }


return 0;
}
