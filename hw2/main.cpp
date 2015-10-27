#include "algorithms.hpp"
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <numeric>
#include <algorithm>    // std::merge, std::sort


int main(){
	
    /* All functions require a vector for register coins AND a zeroed out
	  vector for marking coins used.  Must clear used after each function
	  call or create new used */
     
    std::string inFilename;
    std::string outFilename;
    std::ifstream input;
    std::ofstream output;
    std::vector<std::string> reading;       // holds lines from input file
    std::vector<int> converted;             // holds actual int values
    std::string line;
    std::string initialVal;                 // odd lines on input file
    int val;                                // converted value to be coin-changed
    int result;                             // result from algo call
    int choice;

    std::cout << "Enter the name of the file to open: ";
    std::cin >> inFilename;
    std::cout << "Please enter 0 for Divide and Conquer, 1 for DP, 2 for Greedy: ";
    std::cin >> choice;

    // open specified file
    input.open(inFilename.c_str());
    if (!input.is_open()) {
        std::cout << "Error opening input file.\n";
    }

    // read data in from file
    while(std::getline(input, line)) {
        reading.push_back(line);
    }

    // close file
    input.close();
    if (input.is_open()) {
        std::cout << "Error closing input file.\n";
    }

    // assuming all input files are .txt for now
    inFilename.erase(inFilename.end()-4, inFilename.end());

    outFilename = inFilename + "change.txt";

    // open output file for results
    output.open(outFilename.c_str());
    if (!output.is_open()) {
        std::cout << "Error opening output file.\n";
    }

    std::string checkMe = reading[1];
    //problem 5 - array, array, value ... etc
    if(checkMe[0] == '['){
        for (int i = 0; i < reading.size(); i++) {
            line = reading[i];

            // positive lines contain the array
            if (i % 3 == 0) {
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
                //second array                
                while (found!=std::string::npos) {
                    line[found]=' ';
                    found=line.find_first_of("[,]",found+1);
                }

                // tokenize based off spaces
                toTokenize = line.c_str();
                token = strtok((char*) toTokenize, " ");
                while(token != NULL){
                    int temp = atoi(token);
                    //if not in vector already, add, sort
                    if(std::find(converted.begin(), converted.end(), temp) == converted.end()){
                        converted.push_back(temp);
                        std::sort(converted.begin(), converted.end());
                    }
                    token = strtok(NULL, " ");
                }
                // now that converted holds all the integers, pull the value
                // being searched for from the next line
                line = reading[i+2];
                val = atoi(line.c_str());

                // call sorting function
                std::vector<int> used (converted.size(), 0);

//CHANGE ALGO HERE
                if(choice == 0){
                    used = changeslow(converted, val, converted.size());
                    result = arraySum(used, used.size());
                }
                else if(choice == 1)
                    result = changegreedy(converted, val, used);
                else if(choice == 2)              
                    result = changedp(converted, val, used);

                // opening bracket
                output << "[";

                // write to output file
                for (int j = 0; j < used.size(); j++) {
                    if (j == used.size() - 1) {
                        output << used[j];
                    }
                    else {
                        output << used[j] << ", ";
                    }
                }

                // closing bracket
                output << "]\n";

                // then output number of coins used
                output << result << "\n";
            }
        }
    }
    //even lines, problems 4 and 6
    else{
    
        for (int i = 0; i < reading.size(); i++) {
            line = reading[i];

            // positive lines contain the array
            if (i % 2 == 0) {
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

                // now that converted holds all the integers, pull the value
                // being searched for from the next line
                line = reading[i+1];
                val = atoi(line.c_str());

                // call sorting function
                std::vector<int> used (converted.size(), 0);
//CHANGE ALGO HERE    
                if(choice == 0){
                    used = changeslow(converted, val, converted.size());
                    result = arraySum(used, used.size());
                }
                else if(choice == 1)
                    result = changegreedy(converted, val, used);
                else if(choice == 2)              
                    result = changedp(converted, val, used);

                // opening bracket
                output << "[";

                // write to output file
                for (int j = 0; j < used.size(); j++) {
                    if (j == used.size() - 1) {
                        output << used[j];
                    }
                    else {
                        output << used[j] << ", ";
                    }
                }

                // closing bracket
                output << "]\n";

                // then output number of coins used
                output << result << "\n";
            }
        }
    }


	/* All functions require a vector for register coins AND a zeroed out
	  vector for marking coins used.  Must clear used after each function
	  call or create new used */

/*
//algo testing - comment out or delete section when running assignment 
	  int count = -1;
	  int value = 2000;
	  static const int temp[] = {1, 2, 4, 6, 8, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
	  std::vector<int> coins (temp, temp+sizeof(temp)/sizeof(temp[0]));
	  std::cout << "Size of vector: " << coins.size() << std::endl;
	  std::vector<int> used (coins.size(), 0);
	  int length = coins.size();

	  std::cout << "- Brute Force -" << std::endl;
	  //used = changeslow(coins, value, length);
	  count = std::accumulate(used.begin(), used.end(), 0);
	  std::cout << "Count is: " << count << std::endl;
	  std::cout << "Coins used: [";
	  for(int i =0; i < used.size(); i++){
	  	if(i == used.size()-1){
	  		std::cout << used[i];
	  	}
	  	else{
	  		std::cout << used[i] << ", ";
	  	}
	  }
	  std::cout << "]" << std::endl;
	  std::cout << "\n";

	  value = 2002;
	  std::cout << "- Greedy -" << std::endl;
	  std::fill(used.begin(), used.end(), 0);
	  count = changegreedy(coins, value, used);
	  std::cout << "Count is: " << count << std::endl;
	  std::cout << "Coins used: [";
	  for(int i =0; i < used.size(); i++){
	  	if(i == used.size()-1){
	  		std::cout << used[i];
	  	}
	  	else{
	  		std::cout << used[i] << ", ";
	  	}
	  }
	  std::cout << "]" << std::endl;
	  std::cout << "\n";

	  value = 2002;
	  std::cout << "- Dynamic Programming -" << std::endl;
	  std::fill(used.begin(), used.end(), 0);
	  count = changedp(coins, value, used);
	  std::cout << "Count is: " << count << std::endl;
	  std::cout << "Coins used: [";
	  for(int i =0; i < used.size(); i++){
	  	if(i == used.size()-1){
	  		std::cout << used[i];
	  	}
	  	else{
	  		std::cout << used[i] << ", ";
	  	}
	  }
	  std::cout << "]" << std::endl;
	  std::cout << "\n";

*/
	return 0;
}
