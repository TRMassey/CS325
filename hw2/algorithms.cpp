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
std::vector<int> changeslow(std::vector<int> coins, int amount, int length) {
    int numCoins;//track min # of coins
    int best = -1;//helps determine min # of coins
    std::vector<int> coinTrack (coins.size(), 0);//track # of coins to find value
    std::vector<int> coinAdd (coins.size(), 0);//add to # of coins to find value
    std::vector<int> used (coins.size(), 0);//track numOfCoins of all coins in array

    //base case, when amount is reached
    if (amount == 0)
    {
	   return used;
    }
    //itereate to see if value is same as any single coin denomination
    for (int i = 0; i < length; i++)
    {
	   if (coins[i] == amount)
	   {
		  //if the same then return that value with denomiation count incremented
		  used[i]++;
		  return used;
	   }
    }
    //loop to find min coins and # of coins for each denomination
    for (int i = 0; i < length; i++)
    {
	   if (coins[i] < amount)
	   {
	   	  //find the min number of coins needed to make K-i cents
		  coinTrack = changeslow(coins, amount - coins[i], length);
		  //find the min number of coins needed to make i cents
		  coinAdd = changeslow(coins, coins[i], length);
		  //loop to find # of coins for each denomination
		  for (int j = 0; j < length; j++)
		  {
			 coinTrack[j] = coinTrack[j] + coinAdd[j];
		  }
		  //summing the number of coins
		  numCoins = arraySum(coinTrack, length);
		  //conditional statement to find min # of coins
		  if (best == -1 || numCoins < best)
		  {
			 //update new min
			 best = numCoins;
			 //loop to save # of each coin used to find value
			 for (int k = 0; k < length; k++)
			 {
				used[k] = coinTrack[k];
			 }
		  }
	   }
    }
    return used;//return the num of coins used vector
}


/************************************************************
Helper function for slowchange.  After array is located with 
min amount of each denomiation of coins, add coin amounts to
get total min coins.
************************************************************/
int arraySum(std::vector<int> used, int sizeOfArray){  
    int sum = 0;
    //iterate through used coin array
    for (int i = 0; i < sizeOfArray; i++)
    {
	   sum = sum + used[i];
    }
    return sum;  //this is the min count
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
	//assert(coins.size() != 0);

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
	//assert(coins.size() != 0);

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

