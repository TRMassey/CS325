#include <algorithm.h>
#include <vector>

/****************************************************
Funcction: algorithm1
Purpose: Enumeration
Time Complexity: O(n^3)
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
Funcction: algorithm2
Purpose: Better Enumeration
****************************************************/