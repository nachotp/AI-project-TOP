#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "helper.h"

using namespace std;

int getProgenitor(vector<float> &cum_score){
    return lower_bound(cum_score.begin(), cum_score.end(), rand() % ((int)cum_score.back())) - cum_score.begin();
}

vector<float> generateProbVector(int n){
    vector<float> chances;
    
    for(int i = 0; i < n; i++){
        chances.push_back((double)rand() / RAND_MAX);
    }
    
    return chances;
}