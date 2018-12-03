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

float Route::totalDistance(vector <vector <float>> &weights){
    float total = weights[0][seq[0]];   
    for(size_t i = 1; i < seq.size(); ++i){
        total += weights[seq[i]][seq[i-1]];
    }
    total += weights[seq.back()][n-1];
    return total;
}

int Route::totalScore(vector<Node> &nodes){
    int total = 0;
    for (int i : seq) total += nodes[i].score;
    return total;
}

void Route::generateInitial(){
    seq.resize(n-2);
    for(size_t i = 1; i < n-1; i++) seq[i-1] = i;
    random_shuffle(seq.begin(), seq.end());
    seq.resize(rand()%seq.size() + 1);
}

std::ostream& operator<< (std::ostream &out, Route const& ruta) {
    out << "0-";
    for (int i : ruta.seq){
        out << i << "-";
    }
    out << ruta.n - 1 << ' ';
    return out;
}