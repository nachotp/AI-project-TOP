#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "helper.h"
#include "node.h"
#include "route.h"
#include "solution.h"

#define INITIAL_GENE_POOL 1000
#define TOP_AMOUNT 100
#define MAX_GENERATIONS 1
#define PC 0.5
#define PM 0.3

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

    vector<Solution> epoch, progenitors;
    vector<float> cum_score, transform_chance;
    Solution best;

    cout << "Pool inicial de" << INITIAL_GENE_POOL << " soluciones";
    for (size_t i = 0; i < INITIAL_GENE_POOL; i++){
        epoch.push_back(Solution(n, m));
        //cout << epoch[i];
        epoch[i].eval(weights, nodes, tmax);
    }

    for(size_t gen = 0; gen < MAX_GENERATIONS; ++gen){

         sort(epoch.begin(), epoch.end());

            if (best < epoch.back()) best = epoch.back();

            // Selección de las TOP_AMOUNT mejores soluciones
            progenitors = vector<Solution>(epoch.rbegin()+1, epoch.rbegin()+TOP_AMOUNT);
            epoch.clear();

            progenitors.push_back(best);
            cout << "Epoch best: " << best.getScore() << " con penalti de " << best.penalti << "\n";
            cout << progenitors.size() << " Progenitores\n";

            // Generar rangos para selección por ruleta
            cum_score.push_back(0);
            for (size_t i = 0; i< progenitors.size(); ++i){
                cum_score.push_back(cum_score.back() + abs(progenitors[i].getScore()));
            }

            

            int select = getProgenitor(cum_score);

            cout << "Progenitor "<< select << '\n' << progenitors[select] << '\n';

    }

    return 0;
}