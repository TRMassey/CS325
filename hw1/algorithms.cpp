#include "algorithms.hpp"
#include <vector>
#include <iostream>
#include <limits.h>	 //for relative -infinity (INT_MIN) 

/****************************************************
Funcction: algorithm1
Purpose: Enumeration
Time Complexity: O(n^3), two nested loops
Input: vector of integers, representing one problem set
from the file input in main
Output: Returns the maximum sum
****************************************************/
int algorithm1(std::vector<int> inputArray){
	int maxSum = 0;

	for(int i=0; i < inputArray.size(); i++){
		for(int j=i; j < inputArray.size(); j++){
			int sum = 0;
			for(int k = i; k <= j; k++){			// O(j-1)
				sum = sum + inputArray[k];
			if(sum > maxSum)
				maxSum = sum;
			}
		}
	}

	return maxSum;
}


/****************************************************
Function: algorithm2
Purpose: Better Enumeration
Run Time: O(n^2), one nested loop
Input: vector of integers, representing one problem set
from the file input in main
Output: Returns the maximum sum
****************************************************/
int algorithm2(std::vector<int> &inputArray){
	int maxSum = 0;

	for(int i = 0; i < inputArray.size(); i++){
		int sum = 0;
		for(int j = i; j < inputArray.size(); j++){		// O(n^2)
			sum = sum + inputArray[j];
			if(sum > maxSum)
				maxSum = sum;
		}
	}

	return maxSum;
}


/****************************************************
Funcction: Algo3_Midpoint
Purpose: Find the midpoint max sum for divide and 
conquer
Time Complexity: O(2n) = O(n)
Input: vector of integers, representing one problem set
from the file input in main, int starting point, int 
ending point
Output: Returns the maximum sum of mid
****************************************************/
int algo3_Midpoint(std::vector<int>&input, int start, int mid, int end){
	int leftSum = INT_MIN, rightSum = INT_MIN;	//rep neg infinity
	int sum = 0;
	int index, maxR, maxL;

	//iterate from mid to low
	for(index = mid; index >= start; index--){
		sum += input[index];
		if (sum > leftSum){
			leftSum = sum;
			//maxL = index;	don't use if not doing tuple solution
		}
	}
	//reset sum and iterate from mid to high
	sum = 0;
	for(index = mid+1; index < end; index++){
		sum += input[index];
		if(sum > rightSum){
			rightSum = sum;
			//maxR = index; don't use if not doing tuple solution
		}
	}
	return leftSum + rightSum;
}


/****************************************************
Funcction: algorithm3 (adapted from 'Introduction to
Algorithms, Third Ed.' pp71-72)
Purpose: Divide and Conquer
Time Complexity: O(nlgn), T(n) = 2T(n/2) + O(n)
Input: vector of integers, representing one problem set
from the file input in main, int starting point, int 
ending point
Output: Returns the maximum sum
****************************************************/
int algorithm3(std::vector<int>&input, int start, int end)
{
	//base case, 1 element
	if(start == end){
		return input[start];
	}
	else{
		//find the mid
		int mid = (start + end)/2;
		//find max in left, right (divide and conquer), cross (linear)
		int l_sum = algorithm3(input, start, mid);
		int r_sum = algorithm3(input, mid+1, end);
		int m_sum = algo3_Midpoint(input, start, mid, end);

		//determine overall max
		if(l_sum >= r_sum && l_sum >= m_sum){
			return l_sum;
		}
		else if(r_sum >= l_sum && r_sum >= m_sum){
			return r_sum;
		}
		else{
			return m_sum;
		}
	}

}


/****************************************************
Funcction: algorithm4 (algo2, disreguard negative values)
Purpose: Linear-time
Time Complexity: O(n)
Input: vector of integers, representing one problem set
from the file input in main
Output: Returns the maximum sum
****************************************************/
int algorithm4(std::vector<int>&input)
{
	int max = 0, sum = 0, index = 0;

	//non-recursive, linear
	for(index=0; index < input.size(); index++){
		sum += input[index];
		//if we just added neg, disregard
		if(sum > max){
			max = sum;
		}
		//if we just went neg, disregard
		else if(sum < 0){
			sum = 0;
		}
	}
	return max;
}	