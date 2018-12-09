#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "helper.h"

using namespace std;

int getProgenitor(vector<float> &cum_score){
    return lower_bound(cum_score.begin(), cum_score.end(), rand() % ((int)cum_score.back() + 1)) - cum_score.begin();
}

vector<float> generateProbVector(int n){
    vector<float> chances = vector<float>(n);
    generate(chances.begin(), chances.end(),[](){
        return (double)rand() / RAND_MAX;
        });
    return chances;
}