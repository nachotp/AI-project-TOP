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
    routes = cromosome();
}

Solution::Solution(int n, int m){
    m_ = m;
    n_ = n;
    for (int i = 0; i < m; ++i)
        routes.push_back(Route(n_, true));
}

Solution::Solution(int n, int m, cromosome cross_result){
    m_ = m;
    n_ = n;
    routes = cross_result;
}

float Solution::eval(vector<vector<float>> &weights, vector<Node> &nodes, int tmax, int penalti_multiplier){
    visited = vector<bool>(n_, 0);
    distances = vector<float>();
    distances.reserve(m_);
    score = 0;
    penalti = 0;
    for (Route rt : routes){
        if (rt.size() == 0) exit(1);
        float dist = rt.totalDistance(weights);
        rt.markVisit(visited);
        distances.push_back(dist);
        if (tmax < dist)
            penalti += penalti_multiplier * dist;
    }

    for(int i = 1; i < n_; i++) score += visited[i]*nodes[i].score;

    return score-penalti;
}

float Solution::getScore(){
    return score - penalti;
}
 
void Solution::mutate(vector<vector<float>> weights, float &tmax){
    switch(rand() % pos_mutations){
        case 0: 
            seqModMutator(0);
            break;
        case 1:
            seqModMutator(1);
            break;
        case 2:
            lengthFixingMutator(weights, tmax);
            break;
    }
}

void Solution::seqModMutator(int type){
    int modding = rand() % m_;
    if (routes[modding].size() > 1){
        int min = rand() % (routes[modding].size() - 1), max;
        do {
            max = rand() % routes[modding].size();
        } while (max <= min);

        
        switch (type) {
            case 0:
                routes[modding].flipSeq(min, max);
                break;
            case 1:
                routes[modding].scrambleSeq(min, max);
                break;
        }
        
    }
}

void Solution::lengthFixingMutator(vector<vector<float>> weights, float &tmax){
    int max = max_element(distances.begin(), distances.end()) - distances.begin();
    int min = min_element(distances.begin(), distances.end()) - distances.begin();
    if (distances[max] > tmax){
        routes[max].reduceSeq(weights, tmax);
    } else if (distances[min] < tmax){
        visited = vector<bool>(n_, 0);
        for (Route rt : routes) rt.markVisit(visited);
        routes[min].expandSeq(weights, visited, tmax);
    }

}

Solution Solution::crossOver(Solution &b){
    int slice = rand() % (m_ - 1) + 1;
    cromosome new_routes = cromosome();
    for (int i = 0; i < m_; ++i) {
        new_routes.push_back((i < slice) ? routes[i] : b.routes[i]);
    }

    return Solution(n_, m_, new_routes);
}

std::ostream &operator<<(std::ostream &out, Solution const &sol){
    for(size_t i = 0; i < sol.routes.size(); ++i){
        out << sol.distances[i] << " ";
        out << sol.routes[i] << '\n';
    }
    return out;
}

bool operator< ( Solution const& a, Solution const& b){
    float resA = a.score - a.penalti;
    float resB = b.score - b.penalti;
    return resA < resB;
};
