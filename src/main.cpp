#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "helper.h"
#include "node.h"
#include "route.h"
#include "solution.h"

#define GENE_POOL_SIZE 5000
#define TOP_AMOUNT 100
#define MAX_GENERATIONS 50
#define PC 0.3
#define PM 0.2
#define PENALTI 10

using namespace std;

int main(int argc, char const *argv[]){
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
    
    float x, y;
    int score;

    for(size_t i = 0; i < n; ++i){
        cin >> x >> y >> score;
        nodes.push_back(Node(x,y,score));
        weights[i][i] = tmax;
    }


    // Generate distances matrix
    float dist;
    for(size_t i = 0; i < n; ++i){
        for(size_t j = i+1; j < n; ++j){
            dist = eucDist(nodes[i], nodes[j]);
            weights[i][j] = dist;
            weights[j][i] = dist;
        }
    }

    vector<Solution> epoch, progenitors;
    vector<double> accum_score;
    vector<float> transform_chance;
    Solution best;

    // Initial gene pool of  GENE_POOL_SIZE solutions
    for (size_t i = 0; i < GENE_POOL_SIZE; i++){
        epoch.push_back(Solution(n, m));
        epoch[i].eval(weights, nodes, tmax, PENALTI);
    }

    for(size_t gen = 0; gen < MAX_GENERATIONS; ++gen){
        sort(epoch.begin(), epoch.end());
        if(!gen) cerr << epoch.back().getScore() << ";";

        // Store global best solution to assure no quality loss
        if (gen == 0 || best < epoch.back()) best = epoch.back();

        // TOP_AMOUNT highest ranked solutions
        progenitors = vector<Solution>(epoch.rbegin()+1, epoch.rbegin()+TOP_AMOUNT);
        epoch = vector<Solution>(progenitors);
        epoch.reserve(GENE_POOL_SIZE-TOP_AMOUNT);

        progenitors.push_back(best);

        // Cumulative score for rulette selection
        accum_score = vector<double>();
        accum_score.push_back(progenitors[0].getScore());
        for (size_t i = 1; i< progenitors.size(); ++i){
            accum_score.push_back(accum_score.back() + abs(progenitors[i].getScore()));
        }

        
        transform_chance = generateProbVector(progenitors.size());

        int select, select2;

        // Crossing over
        while (epoch.size() < GENE_POOL_SIZE-1){
            select = getProgenitor(accum_score);
            while (transform_chance[select] > PC) select = getProgenitor(accum_score);

            select2 = getProgenitor(accum_score);
            while (transform_chance[select2] > PC || select == select2) select2 = getProgenitor(accum_score);

            epoch.push_back(progenitors[select].crossOver(progenitors[select2]));
            epoch.back().eval(weights, nodes, tmax, PENALTI);

            epoch.push_back(progenitors[select2].crossOver(progenitors[select]));
            epoch.back().eval(weights, nodes, tmax, PENALTI);
        }

        // Mutation
        transform_chance = generateProbVector(epoch.size());
        for (size_t i = 0; i < epoch.size(); i++) {
            if (transform_chance[i] < PM){
                epoch[i].mutate(weights, tmax);
                epoch[i].eval(weights, nodes, tmax, PENALTI);
            }
            
        }

        epoch.push_back(best);
        epoch.back().mutate(weights, tmax);
        epoch.back().eval(weights, nodes, tmax, PENALTI);
    }

    sort(epoch.begin(), epoch.end());

    cout << epoch.back().getScore() << '\n' << epoch.back();

    return 0;
}