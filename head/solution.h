#ifndef SOLUTION_CLASS
#define SOLUTION_CLASS

#include "route.h"
#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<Route> cromosome;

class Solution {
    private:
        static const int pos_mutations = 1;
        int m_, n_;
        float score;

    public:
        cromosome routes;
        float penalti;
        Solution(int n, int m);
        Solution(int n, int m, cromosome cross_result);
        Solution();
        float eval(vector<vector<float>> &weights, vector<Node> &nodes, int tmax, int penalti_multiplier);
        float getScore();
        void mutate();
        void seqFlipMutator();
        Solution crossOver(Solution &b);
        friend std::ostream &operator<<(std::ostream &out, const Solution &sol);
        friend bool operator< ( Solution const& a, Solution const& b);
};

#endif