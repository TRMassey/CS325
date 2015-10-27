
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
    std::cout << "Please enter 1 for Greedy and 2 for DP: ";
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

    outFilename = inFilename + "results.txt";

    // open output file for results
    output.open(outFilename.c_str());
    if (!output.is_open()) {
        std::cout << "Error opening output file.\n";
    }


    //problem 5 - array, array, value ... etc
        for (int i = 0; i < reading.size(); i++) {
            std::string readme = reading[i];
		if(readme[0] != '['){
			output << readme << '\n';
		}
	}

return 0;
}

 
