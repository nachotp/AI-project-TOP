#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "node.h"
#include "route.h"
#include "solution.h"

using namespace std;

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    srand(time(NULL));
    unsigned int n, m;
    float tmax;
    string d;
    cin >> d >> n;
    cin >> d >> m;
    cin >> d >> tmax;
    d.clear();

    vector<vector<float>> weights(n, vector<float>(n));

    vector<Node> nodes;
    
    cout << n << " nodos " << m << " rutas en tiempo " << tmax << '\n';
    float x, y;
    int score;

    cout << "Lectura de nodos." << '\n';

    for(size_t i = 0; i < n; ++i){
        cin >> x >> y >> score;
        nodes.push_back(Node(x,y,score));
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

    vector<Solution> epoch;

    for (size_t i = 0; i < 1000; i++){
        epoch.push_back(Solution(n, m));
        cout << epoch[i];
    } 
    
    return 0;
}
