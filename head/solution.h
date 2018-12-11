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
        static const int pos_mutations = 3;
        int m_, n_;
        float score;
        vector<bool> visited;
        vector<int> distances;

    public:
        cromosome routes;
        float penalti;
        Solution(int n, int m);
        Solution(int n, int m, cromosome cross_result);
        Solution();
        float eval(vector<vector<float>> &weights, vector<Node> &nodes, int tmax, int penalti_multiplier);
        float getScore();
        Solution crossOver(Solution &b);
        void mutate(vector<vector<float>> weights, float &tmax);
        void seqModMutator(int type);
        void lengthFixingMutator(vector<vector<float>> weights, float &tmax);
        friend std::ostream &operator<<(std::ostream &out, const Solution &sol);
        friend bool operator< ( Solution const& a, Solution const& b);
};

#endif