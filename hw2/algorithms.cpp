#include "algorithms.hpp"
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <limits.h>

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
int changeslow(std::vector<int> coins, int index, int value, std::vector<int> &used){
	int count = INT_MAX;			//to compare total result to sub result
	int subCount = 0;				//holds sub-results from recursion
	int finalCount = INT_MAX;		//following variables for used vector result
	int vSub = 0;					
	int vCount = INT_MAX;
	int vVal;

	//error if no coins
	assert(coins.size() != 0); 

	//recursive work to locate min result
	//base case - finished making change
	if(value == 0){
		return 0;		// don't increment count
	}
	//else divide into subproblems- for each i<k
	for(int i = 0; i < index; i++){
		//find the min number of coins needed to make i cents
		if(coins[i] <= value){
			//find the min number of coins needed to make K-i cents
			subCount = changeslow(coins, index, value - coins[i], used);
			//chose the i that minimizes this sum
			if(subCount != INT_MAX && subCount+1 < count){
				count = subCount + 1;					
			}
		}
	}
	//Prep for writing results to used coins vector, preserve needed values
	finalCount = count;
	vVal = value;
	vCount = 0;
	int x = index-1;
	//use the final count to locate what the current min coin amount is
	while(vCount != finalCount && x >= 0){
		vSub = (vVal/coins[x]);	//simplify recursive work done above since we can compare results
		vVal -= vSub * coins[x];	
		vCount += vSub;
		//std::cout << vCount << " vs. " << finalCount << std::endl;
		//compare with results from recursive work
		if(vCount > finalCount){  //this is wrong, clear anything written to vector
			vVal = value;
			vCount = 0;
			std::fill(used.begin(), used.end(), 0);
		}
		else{  //this is potentially right, write it and keep checking
			used[x] = vSub;
		}
		x--;	//decrement through the coins
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
	std::vector<int> tempUsed (coins.size(), 0);	//vectors inside vTable
	std::vector< std::vector<int> > vTable (value+1, tempUsed); //table of vector coins used solutions

	//if value == 0
	table[0] = 0;

	//error if no coins
	assert(coins.size() != 0); 

	//make table of all results
	//iterate through positive, non-zero value optons
	for(int sum = 1; sum <= value; sum++){
		int subVal = value;
		//iterate through all possible coin options
		for(int coin = coins.size()-1; coin >= 0; coin--){
			//is the coin an option?
			if(coins[coin] <= sum){
				subCount = table[sum-coins[coin]];
				//find min
				if(subCount != INT_MAX && subCount+1 < table[sum]){
					table[sum] = subCount+1;
					vTable[sum][coin] = sum/coins[coin];
					std::cout << vTable[sum][coin] << std::endl;
					if(subVal > coins[coin]){
						subVal -= (subVal/coins[coin])*coins[coin];
					}
				}
			}		
		}
	}
	for(int x = 0; x < used.size(); x++){
		used[x] = vTable[value][x];
	}

	//return array of coins used
	return table[value];
}



/*currently have only been working on dp.  My original version found the correct count
based off of dp and then used a version of greedy to find the vector results.  Then I saw
that there is a situation where greedy is supposed to return an incorrect answer while the
other two are not:

Suppose V = [1, 3, 7, 12] and A = 29. The changegreedy should return C = [2, 1, 0, 2] with m = 5
and changedp and slowchange should return C = [0, 1, 2, 1] with m = 4. The minimum number of coins m
= 4. 

So... I tried a bunch of ideas and have been spending the most time trying to figure out
how to do the same idea from dp for arrays.  So we would need to make a vector of vectors.
vector[x][y]  where x is the value (similar to what we have for finding the count) and y
is the coins.  So at vector[value] holds [0, 1, 2, 1] where the count is 4.

Totally open to other ideas!

*/