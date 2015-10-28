
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


int main(){

	/* All functions require a vector for register coins AND a zeroed out
	  vector for marking coins used.  Must clear used after each function
	  call or create new used */
    std::string inFilename;
    std::string outFilename;
    std::string outFilename2;
    std::ifstream input;
    std::ofstream output;
    std::ofstream output2;
    std::vector<std::string> reading;       // holds lines from input file
    std::vector<int> converted;             // holds actual int values
    std::string line;
    std::string initialVal;                 // odd lines on input file
    int val;                                // converted value to be coin-changed
    int result;                             // result from algo call

    

    outFilename = "problems.txt";
    outFilename2 = "smallproblems.txt";
    // open output file for results
    output.open("problems.txt");
    if (!output.is_open()) {
        std::cout << "Error opening output file.\n";
    }
    output2.open("smallproblems.txt");
    if (!output2.is_open()) {
        std::cout << "Error opening output file.\n";
    }
    std::cout << "Pick problem 4, 5, or 6: \n";
    std::cin >> val;

    if(val == 4){
       // problem 4
         for (int i = 0; i < 2201; i++) {
            output << "[1, 5, 10, 25, 50]\n";
            output << i << "\n";
        }
        for(int i = 10; i < 50; i++){
            output2 << "[1, 5, 10, 25, 50]\n";
            output2 << i << "\n";
        }
    }

    else if(val == 5){
        // problem 5
        for (int i = 2000; i < 2201; i++) {
            output << "[1, 2, 6, 12, 24, 48, 60]\n";
            output << "[1, 6, 13, 37, 150]\n";
            output << i << "\n";
        }
        for(int i = 10; i < 35; i++){
            output2 << "[1, 2, 6, 12, 24, 48, 60]\n";
            output2 << "[1, 6, 13, 37, 150]\n";
            output2 << i << "\n";
        }
    }

    else{
     // problem 6 ---- causes an erro rin the program!! Seg fault. Coins 0.
         for (int i = 2000; i < 2201; i++) {
            output << "[1, 2, 4, 6, 8, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30]\n";
             output << i << "\n";
         }
        for(int i = 10; i < 50; i++){
 output2 << "[1, 2, 4, 6, 8, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30]\n";
            output2 << i << "\n";
        }
    }

 //   output.close("problems.txt");

    return 0;
}
