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
	std::vector<int> temp2;
	std::vector< std::vector<int> > temp;
	int tempValue = value;
	int tracker = 0;
	bool found = false;

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
			
			//trying to do what Joseph suggests https://oregonstate.instructure.com/courses/1555021/discussion_topics/7617682
			if(tracker != value){
				tracker += 1;
				temp2.push_back(coins[i]);
			}
			else{
				temp.push_back(temp2);
				temp2.clear();
				tracker = 1;
				temp2.push_back(coins[i]);

			}
			//find the min number of coins needed to make K-i cents
			subCount = changeslow(coins, index, value - coins[i], used);
			//chose the i that minimizes this sum
			if(subCount != INT_MAX && subCount+1 < count){
				count = subCount + 1;		
			}
		}
	}
	temp.push_back(temp2);

	//look through vector of vectors to find which solution equals count
	for(int i=0; i < temp.size(); i++){
		tracker = 0;
		for(int j = 0; j < temp2.size(); j++){
			tracker += temp[i][j];
			if(tracker == count && j == temp2.size()-1){
				found = true;
				//get the singular counts by counting multiples
				for(int x=0; x < temp2.size(); x++){
					int mults =1;
					int y = x+1;
					while(temp2[y] != temp2[x]){
						mults += 1;
						y += 1; 
					}
					used[x] = mults;
				}
			}
		}
		if (found){
			break;
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


