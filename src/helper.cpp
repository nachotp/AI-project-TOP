#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

#include "helper.h"

using namespace std;

int getProgenitor(vector<double> &accum_score){
    if (accum_score.back() < 0) exit(1);
    int select = rand() % ((int)accum_score.back());
    return lower_bound(accum_score.begin(), accum_score.end(), select) - accum_score.begin();
}

vector<float> generateProbVector(int n){
    vector<float> chances;
    
    for(int i = 0; i < n; i++){
        chances.push_back((double)rand() / RAND_MAX);
    }
    
    return chances;
}