#include "ruckzack_solver.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

KnapsackSolver::KnapsackSolver(int cap, int num) : capacity(cap), n(num) {
    srand(time(0));
}

void KnapsackSolver::readItems() {
    for (int i = 0; i < n; i++) {
        int v, w;
        std::cin >> v >> w;
        items.push_back({w, v});
    }
}

int KnapsackSolver::get_weight(const std::vector<int>& g) {
    int sw = 0;
    for (int i = 0; i < n; i++) {
        if (g[i]) sw += items[i].w;
    }
    return sw;
}

int KnapsackSolver::get_profit(const std::vector<int>& g) {
    if (get_weight(g) > capacity) return 0;
    int sv = 0;
    for (int i = 0; i < n; i++) {
        if (g[i]) sv += items[i].v;
    }
    return sv;
}

int KnapsackSolver::solve() {
    int pop_size = 50;
    int gens = 1000;
    std::vector<std::vector<int>> pop(pop_size, std::vector<int>(n));

    for (int i = 0; i < pop_size; i++) {
        for (int j = 0; j < n; j++) {
            pop[i][j] = rand() % 2;
        }
    }

    int best_v = 0;

    for (int g = 0; g < gens; g++) {
        std::sort(pop.begin(), pop.end(), [&](const std::vector<int>& a, const std::vector<int>& b) {
            return get_profit(a) > get_profit(b);
        });

        int cur_v = get_profit(pop[0]);
        if (cur_v > best_v) best_v = cur_v;

        for (int i = pop_size / 2; i < pop_size; i++) {
            int p1 = rand() % (pop_size / 2);
            int p2 = rand() % (pop_size / 2);
            int cp = rand() % n;
            
            for (int j = 0; j < n; j++) {
                if (j < cp) pop[i][j] = pop[p1][j];
                else pop[i][j] = pop[p2][j];
            }

            if (rand() % 10 == 0) {
                int mp = rand() % n;
                pop[i][mp] = 1 - pop[i][mp];
            }
        }
    }

    return best_v;
}
