#include "algorithms.hpp"
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <limits.h>

/**********************************************************
Funcction: changeslow
Purpose: Brute Force/ Divide and Conquer
Time Complexity: exponential O(2^n)
Input: sorted array/vector of coins in register, int end of
array, value of change that needs to be made, array/vector of
used coins.
Notes: Adapted from pseudocode, code, and discussion found at
http://www.algorithmist.com/index.php/Min-Coin_Change
http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
**********************************************************/
int changeslow(std::vector<int> coins, int index, int value, std::vector<int> &used){
	int count = INT_MAX;			//to compare total result to sub result
	int subCount = 0;				//holds sub-results from recursion

	//error if no coins
	assert(coins.size() != 0); 

	//base case - finished making change
	if(value == 0){
		return 0;		// don't increment count
	}

	//else divide into subproblems- for each i<k
	for(int index = 0; index < coins.size(); index++){
			//find the min number of coins needed to make i cents
			if(coins[index] <= value){
				//find the min number of coins needed to make K-i cents
				subCount = changeslow(coins, coins.size(), value - coins[index], used);
			}
			//chose the i that minimizes this sum
			if(subCount != INT_MAX && subCount + 1 < count){
				count = subCount + 1;
				used[index] = count;
			}
			else{
				used[index] = 0;
			}
	}
	return count;
}



/**********************************************************
Funcction: changegreedy
Purpose: Greedy
Time Complexity: O(n^2)
Input: sorted array/vector of coins in register, value
of change that needs to be made, array/vector of used coins.
Notes: Algorithm adapted from discusion and code found at 
http://geeksquiz.com/greedy-algorithm-to-find-minimum-number-of-coins/
titled, "Greedy Algorithm to find Minimum number of Coins".
**********************************************************/
int changegreedy(std::vector<int> coins, int value, std::vector<int> &used){
	int count = 0;						// coins used
	int curMax = 0;						//cur coin closest to val

	//error if no coins
	assert(coins.size() != 0); 

	//iterate through coins starting with largest first
	for(int index = coins.size()-1; index >= 0; index--){
		while(coins[index] <= value){
			value -= coins[index];		//update current val
			used[index] += 1;			//update coins used at index
			count += 1;					//update coin count
		}
		if(value == 0){					//made change completed
			break;
		}
	}	
	//return amount of coins used
	return count;

}



/**********************************************************
Funcction: changedp
Purpose: Dynamic Programming
Time Complexity: O(nk)
Input: Sorted array/vector of coins in register, value of
change that needs to be made, array/vector of used coins.
Notes: Algorithm adapted from discusion and code found at 
http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
titled, "Find minimum number of coins that make a given value".
**********************************************************/
int changedp(std::vector<int> coins, int value, std::vector<int> &used){
	int count = 0;						// coins used
	int subCount;
	std::vector<int> table (value+1, INT_MAX);//table of sub-values

	//if value == 0
	table[0] = 0;

	//error if no coins
	assert(coins.size() != 0); 

	//iterate through positive, non-zero value optons
	for(int sum = 1; sum <= value; sum++){
		//iterate through all possible coin options
		for(int coin = 0; coin <= coins.size(); coin++){
			//is the coin an option?
			if(coins[coin] <= sum){
				subCount = table[sum-coins[coin]];
				//find min
				if(subCount != INT_MAX && subCount+1 < table[sum]){
					table[sum] = subCount+1;
					used[coin] = subCount+1;
				}
			}
		}
	}
	//return array of coins used
	return table[value];
}