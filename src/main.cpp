#include <iostream>
#include <stdio.h>
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
    vector<Punto> nodes;
    cout << n << " nodos " << m << " rutas en tiempo " << tmax << '\n';
    float x, y;
    int score;
    for(size_t i = 0; i < n; ++i){
        cin >> x >> y >> score;
        nodes.push_back(Punto(x,y,score));
    }
    
    
    for(Punto pto : nodes){
        cout << pto;
    }
    

    return 0;
}
