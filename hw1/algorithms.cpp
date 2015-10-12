#include <algorithm.h>
#include <vector>

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

	for(int i=0 i < inputArray.size(); i++){
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
int algorithm2(std::vector<int> inputArray){
	int maxSum = 0;

	for(int i = 0; i < inputArray.size(); i++){
		int sum = 0;
		for(int j = 0; j < inputArray.size(); j++){		// O(n^2)
			sum = sum + inputArray[j];
			if(sum > maxSum)
				maxSum = sum;
		}
	}

	return maxSum;
}