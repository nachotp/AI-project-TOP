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
#define PC 0.25
#define PM 0.11

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

    cout << "Pool inicial de " << INITIAL_GENE_POOL << " soluciones\n";
    for (size_t i = 0; i < INITIAL_GENE_POOL; i++){
        epoch.push_back(Solution(n, m));
        //cout << epoch[i];
        epoch[i].eval(weights, nodes, tmax);
    }

    for(size_t gen = 0; gen < MAX_GENERATIONS; ++gen){
        cout << "Epoch " << gen << ":\n";
         sort(epoch.begin(), epoch.end());

        if (best < epoch.back()) best = epoch.back();

        // Selección de las TOP_AMOUNT mejores soluciones
        progenitors = vector<Solution>(epoch.rbegin()+1, epoch.rbegin()+TOP_AMOUNT);
        epoch.clear();

        progenitors.push_back(best);
        cout << "  - Best: " << best.getScore() << " con penalti de " << best.penalti << "\n";

        // Generar rangos para selección por ruleta
        cum_score.push_back(0);
        for (size_t i = 0; i< progenitors.size(); ++i){
            cum_score.push_back(cum_score.back() + abs(progenitors[i].getScore()));
        }

        transform_chance = generateProbVector(progenitors.size());
        int select = getProgenitor(cum_score);
        int select2 = getProgenitor(cum_score);
        
        cout << "Progenitor " << select << '\n' << progenitors[select] << '\n';
        
        cout << "Progenitor " << select2 << '\n' << progenitors[select2] << '\n';

        cout << "Hijo 1 \n" <<  progenitors[select].crossOver(progenitors[select2]);
        cout << "Hijo 2 \n" <<  progenitors[select2].crossOver(progenitors[select]);
    }

    return 0;
}