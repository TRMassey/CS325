#include "algorithms.hpp"
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <limits.h>
#include <numeric>

/**********************************************************
Funcction: changeslow
Purpose: Brute Force/ Divide and Conquer
Time Complexity: exponential
Input: sorted array/vector of coins in register, int end of
array, value of change that needs to be made, array/vector of
used coins.
Notes: Adapted from pseudocode, code, and discussion found at
http://www.algorithmist.com/index.php/Min-Coin_Change
http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
**********************************************************/
int changeslow (std::vector<int> coins, int amount, std::vector<int> &used) {
	int count = INT_MAX;			//to compare total result to sub result
	int subCount = 0;				//holds sub-results from recursion
	int index = coins.size();
	int finalCount = 0;

	//error if no coins
	assert(coins.size() != 0); 

	// base case, if there is a K-cent coin or value is 0
    if(amount == 0){
    	return 0;
    }
    else if (coins[index-1] == amount) {
        used[index-1] = 1;
        return 1;
    }

    // moves from right to left in sorted array
    // finding the difference between the amount available and given value of i
    for(int i = 0; i < index; i++) {
        //find the min number of coins needed to make i cents
        if (amount >= coins[i]){
            //find the min number of coins needed to make K-i cents
            amount = amount - coins[i];
            used[i] += (coins[i]/coins[i]);
            subCount = changeslow(coins, amount, used);
            if(subCount != INT_MAX && subCount+1 < count){
            	count = subCount + 1;
            	//return count;
            }      
        }
    }
    return count;
}



/**********************************************************
Funcction: changegreedy
Purpose: Greedy
Time Complexity:
Input: sorted array/vector of coins in register, value
of change that needs to be made, array/vector of used coins.
Notes: Algorithm adapted from discusion and code found at
http://geeksquiz.com/greedy-algorithm-to-find-minimum-number-of-coins/
titled, "Greedy Algorithm to find Minimum number of Coins".
**********************************************************/
int changegreedy(std::vector<int> coins, int value, std::vector<int> &used){
	int count = 0;						// coins used

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
Time Complexity:
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
	std::vector<int> temp2 (value, 0);
	int tempValue = value;
	int temp = 0;

	//if value == 0
	table[0] = 0;

	//error if no coins
	assert(coins.size() != 0);

	//make table of all results
	//iterate through positive, non-zero value optons
	for(int sum = 1; sum <= value; sum++){
		int subVal = value;
		//iterate through all possible coin options
		for(int coin = coins.size(); coin >= 0; coin--){
			//is the coin an option?
			if(coins[coin] <= sum){
				subCount = table[sum-coins[coin]];
				//find min
				if(subCount != INT_MAX && subCount+1 < table[sum]){
					table[sum] = subCount+1;
					temp2[sum-1] = coin;			// store coin options here for backtracking
					if(subVal > coins[coin]){
						subVal -= (subVal/coins[coin])*coins[coin];
					}
				}
			}
		}
	}

	// go back through the stored coin, match with original array, and increase count
	// based off of: Dynamic Programming vs. Greedy Algorithms
	// https://alaning.me/index.php/Dynamic_Programming_vs_Greedy_Algorithms
	while(tempValue > 0){					//while value is greater than 0
		temp = coins[temp2[tempValue]];		// store coin value at the previous coin stored
		for(int i = 1; i <= coins.size(); i++){
			if(temp == coins[i]){			// if that value == coins value
				used[i]+=1;					// increase count
			}
		}
		tempValue = tempValue - coins[temp2[tempValue]];
	}

	//return array of coins used
	return table[value];
}

