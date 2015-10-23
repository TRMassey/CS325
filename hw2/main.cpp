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


int main(){
	
	/* All functions require a vector for register coins AND a zeroed out
	  vector for marking coins used.  Must clear used after each function
	  call or create new used */


	  /* algo testing - comment out or delete section when running assignment */
	  int count;
	  int value = 10;
	  static const int temp[] = {1,2,5};
	  std::vector<int> coins (temp, temp+sizeof(temp)/sizeof(temp[0]));
	  std::cout << "Size of vector: " << coins.size() << std::endl;
	  std::vector<int> used (coins.size(), 0);

	  std::cout << "- Brute Force -" << std::endl;
	  count = changeslow(coins, coins.size()-1, value, used);
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

	  value = 10;
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

	  value = 10;
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


	  return 0;
}