#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "punto.h"
#include "route.h"

using namespace std;

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    unsigned int n, m;
    float tmax;
    string d;
    cin >> d >> n;
    cin >> d >> m;
    cin >> d >> tmax;
    d.clear();

    vector<vector<float> > weights(n);

    vector<Punto> nodes;
    cout << n << " nodos " << m << " rutas en tiempo " << tmax << '\n';
    float x, y;
    int score;

    cout << "Lectura de nodos." << '\n';

    for(size_t i = 0; i < n; ++i){
        cin >> x >> y >> score;
        nodes.push_back(Punto(x,y,score));
        weights[i].resize(n);
        weights[i][i] = tmax;
    }

    cout << "Computo de distancias." << '\n';
    float dist;
    for(size_t i = 0; i < n; ++i){
        for(size_t j = i+1; j < n; ++j){
            dist = eucDist(nodes[i], nodes[j]);
            weights[i][j] = dist;
            weights[j][i] = dist;
        }
    }
    
    Route demo = Route(n);
    demo.generateInitial();
    cout << demo << "Costo: " << demo.totalDistance(weights) << " Score " << demo.totalScore(nodes) << '\n';

    return 0;
}
