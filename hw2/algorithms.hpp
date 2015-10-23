#include <iostream>
#include <vector>
#include <map>

int changeslow(std::vector<int> coins, int index, int value, std::vector<int> &used);
int changegreedy(std::vector<int> coins, int value, std::vector<int> &used);
int changedp(std::vector<int> coins, int value, std::vector<int> &used);