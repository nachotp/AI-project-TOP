#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

#include "helper.h"

using namespace std;

int getProgenitor(vector<double> &cum_score){
    if (cum_score.back() < 0) exit(1);
    int select = rand() % ((int)cum_score.back());
    return lower_bound(cum_score.begin(), cum_score.end(), select) - cum_score.begin();
}

vector<float> generateProbVector(int n){
    vector<float> chances;
    
    for(int i = 0; i < n; i++){
        chances.push_back((double)rand() / RAND_MAX);
    }
    
    return chances;
}