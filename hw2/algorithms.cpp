#include "algorithms.hpp"
#include <iostream>
#include <vector>
#include <assert.h>

/**********************************************************
Funcction: changeslow
Purpose: Brute Force/ Divide and Conquer
Time Complexity: exponential O(2^n)
Input: sorted array/vector of coins in register, int end of
array, value of change that needs to be made, array/vector of
used coins.
Notes: Adapted from pseudocode and discussion found at
http://www.algorithmist.com/index.php/Coin_Change#Recursive_Formulation
**********************************************************/
int changeslow(std::vector<int> coins, int index, int value, std::vector<int> &used){
	//error if no coins
	assert(coins.size() != 0); 

	//base case - if recursive call matches value
	if(value == 0){
		//std::cout << coins[index] << std::endl;
		used[index] += 1;			//increment coin use at index
		return 1;					//used for count increment
	}
	if(value < 0 || index <= 0){
		return 0;					//coin doesn't work, don't count
	}

	//else divide into subproblems- for each i<k
	//find the min number of (coins needed to make i cents) + (coins needed to make k-i cents)
	return changeslow(coins, index-1, value, used) + changeslow(coins, index, value-coins[index-1], used);
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
Time Complexity:
Input: Sorted array/vector of coins in register, value of
change that needs to be made, array/vector of used coins.
Notes: Algorithm adapted from discusion and code found at 
http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/
titled, "Dynamic Programming | Set 7 (Coin Change)".
**********************************************************/
int changedp(std::vector<int> coins, int value, std::vector<int> &used){
	int count = 0;						// coins used
	//std::map<int, int> table (1, value);//table of sub-values
	std::vector<int> table (value+1, 0);	//table of sub-values
	std::cout << table.size() << std::endl;
	table[0] = 1;

	//error if no coins
	assert(coins.size() != 0); 

	//update table with 
	for(int index = 0; index < coins.size(); index++){
		for(int coin = coins[index]; coin <= value; coin++){
			table[coin] += table[coin-coins[index]];
			used[index] += 1;
		}
	}
	//return array of coins used
	return table[value];
}