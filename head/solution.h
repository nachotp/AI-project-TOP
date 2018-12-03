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

    public:
        Solution(int n, int m);
        float eval(vector<vector<float>> &weights, vector<Node> &nodes);
        friend std::ostream &operator<<(std::ostream &out, const Solution &sol);
};

#endif