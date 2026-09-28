#ifndef KNAPSACK_SOLVER_H
#define KNAPSACK_SOLVER_H

#include <vector>

struct Item {
    int w, v;
};

class KnapsackSolver {
public:
    KnapsackSolver(int cap, int num);
    void readItems();
    int solve();

private:
    int capacity, n;
    std::vector<Item> items;
    
    int get_profit(const std::vector<int>& g);
    int get_weight(const std::vector<int>& g);
};

#endif
