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
        int m_, n_;
        cromosome routes;
        float score;
        float penalti;

    public:
        Solution(int n, int m);
        Solution();
        float eval(vector<vector<float>> &weights, vector<Node> &nodes, int tmax);
        float getScore();
        friend std::ostream &operator<<(std::ostream &out, const Solution &sol);
        friend bool operator< ( Solution const& a, Solution const& b);
};

#endif