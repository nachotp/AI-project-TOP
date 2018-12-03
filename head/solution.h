#ifndef SOLUTION_CLASS
#define SOLUTION_CLASS

#include "route.h"
#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
    private:
        int m_, n_;
        vector<Route> routes;

    public:
        Solution(int n, int m);
        friend std::ostream &operator<<(std::ostream &out, const Solution &sol);
};

#endif