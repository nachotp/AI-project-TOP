#include "route.h"
#include "solution.h"
#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

Solution::Solution(){
    score = -numeric_limits<float>::max();
    routes = vector<Route>();
}

Solution::Solution(int n, int m){
    m_ = m;
    n_ = n;
    for (int i = 0; i < m; ++i)
        routes.push_back(Route(n_, true));
}

float Solution::eval(vector<vector<float>> &weights, vector<Node> &nodes, int tmax){
    vector<bool> visited = vector<bool>(n_, 0);
    score = 0;
    penalti = 0;
    for (Route rt : routes){
        rt.totalDistance(weights);
        rt.markVisit(visited);
        penalti -= min((float)0, tmax - rt.roundtime);
    }

    
    for(int i = 1; i < n_; i++) score += visited[i]*nodes[i].score;

    return score-penalti;
}

float Solution::getScore(){
    return score - penalti;
}

void Solution::mutate(){

}

std::ostream &operator<<(std::ostream &out, Solution const &sol){
    for(Route rt : sol.routes){
       out << rt << '\n';
    }
    return out;
}

bool operator< ( Solution const& a, Solution const& b){
    float resA = a.score - a.penalti;
    float resB = b.score - b.penalti;
    return resA < resB;
};

Solution crossingOver(Solution a, Solution b){
    return Solution();
}
