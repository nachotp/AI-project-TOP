#include "route.h"
#include "solution.h"
#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

Solution::Solution(int n, int m){
    m_ = m;
    n_ = n;
    for (int i = 0; i < m; ++i)
        routes.push_back(Route(n_, true));
}

float Solution::eval(vector<vector<float>> &weights, vector<Node> &nodes){
    float score = 0;
    for (Route rt : routes) rt.totalDistance(weights);
    vector<bool> visited = vector<bool>(nodes.size(), 0);
    

}

std::ostream &operator<<(std::ostream &out, Solution const &sol){
    for(Route rt : sol.routes){
       out << rt << '\n';
    }
    return out;
}
