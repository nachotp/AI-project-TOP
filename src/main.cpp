#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "punto.h"

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

    float weights[n][n];

    vector<Punto> nodes;
    cout << n << " nodos " << m << " rutas en tiempo " << tmax << '\n';
    float x, y;
    int score;

    cout << "Lectura de nodos." << '\n';

    for(size_t i = 0; i < n; ++i){
        cin >> x >> y >> score;
        nodes.push_back(Punto(x,y,score));
        weights[i][i] = 0;
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
    
    for(size_t i = 0; i < n; ++i){
        for(size_t j =0; j < n; ++j){
            cout << weights[i][j] << '\t';
        }
        cout << '\n';
    }    

    return 0;
}
