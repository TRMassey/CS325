#include <iostream>
#include <vector>
#include <map>

std::vector<int> changeslow(std::vector<int> coins, int amount, int length);
int changegreedy(std::vector<int> coins, int value, std::vector<int> &used);
int changedp(std::vector<int> coins, int value, std::vector<int> &used);


int arraySum(std::vector<int> arr, int sizeOfArray);
