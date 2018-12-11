#include "route.h"
#include "node.h"
#include <vector>
#include <iostream>
#include <ctime> 
#include <cstdlib> 
#include <algorithm>

using namespace std;

Route::Route(int nn, bool populate){
    n = nn;
    if (populate) generateInitial();
}

void Route::append(int elem){
    seq.push_back(elem);
}

int Route::size(){
    return seq.size();
}

void Route::flipSeq(int from, int to){
    reverse(seq.begin()+from, seq.begin()+to);
}

void Route::scrambleSeq(int from, int to){
    random_shuffle(seq.begin() + from, seq.begin() + to);
}

void Route::reduceSeq(vector<vector<float>> &weights, float tmax){
    if (seq.size() <= 1) return;
    int seqmax = seq.size();
    vector<float> costs = vector<float>();
    costs.push_back(weights[0][seq[0]]);
    
    for(int i = 1; i < seqmax; i++){
        costs.push_back(weights[seq[i-1]][seq[i]]);
    }

    costs.push_back(weights[n-1][seq[seq.size()-1]]);

    int max = max_element(costs.begin(), costs.end()) - costs.begin();
    if (max == 0) {
        seq.erase(seq.begin());
    }
    else if (max == seqmax - 1) {
        seq.erase(seq.end()-1);
    }
    else {
        seq.erase(seq.begin() + max-1);
    }
}

float Route::totalDistance(vector <vector <float>> &weights){

    float total = weights[0][seq[0]];   
    for(size_t i = 1; i < seq.size(); ++i){
        total += weights[seq[i]][seq[i-1]];
    }
    total += weights[seq.back()][n-1];
    roundtime = total;
    return total;
}

void Route::markVisit(vector<bool> &visited){
    for(size_t i = 0; i < seq.size(); ++i){
        visited[seq[i]] = true;
    }
}

void Route::generateInitial(){
    seq.resize(n-2);
    for(size_t i = 1; i < n-1; i++) seq[i-1] = i;
    random_shuffle(seq.begin(), seq.end());
    seq.resize(rand()%seq.size() + 1);
}

std::ostream& operator<< (std::ostream &out, Route const& ruta){
    out << "0-";
    for (int i : ruta.seq){
        out << i << "-";
    }
    out << ruta.n - 1 << ' ';
    return out;
}