#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "helper.h"
#include "node.h"
#include "route.h"
#include "solution.h"

#define GENE_POOL_SIZE 1000
#define TOP_AMOUNT 100
#define MAX_GENERATIONS 100
#define PC 0.3
#define PM 0.2
#define PENALTI 5

using namespace std;

int main(){
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
    
    cout << n << " nodes " << m << " routes in " << tmax << " time units\n";
    float x, y;
    int score;

    for(size_t i = 0; i < n; ++i){
        cin >> x >> y >> score;
        nodes.push_back(Node(x,y,score));
        weights[i][i] = tmax;
    }

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

    cout << "Initial gene pool of " << GENE_POOL_SIZE << " solutions\n";
    for (size_t i = 0; i < GENE_POOL_SIZE; i++){
        epoch.push_back(Solution(n, m));
        epoch[i].eval(weights, nodes, tmax, PENALTI);
    }

    for(size_t gen = 0; gen < MAX_GENERATIONS; ++gen){
        cout << "Epoch " << gen+1 << ": "<< epoch.size() << " candidates\n";
        sort(epoch.begin(), epoch.end());

        // Store global best solution to assure no quality loss
        if (gen == 0 || best < epoch.back()) best = epoch.back();

        // TOP_AMOUNT highest ranked solutions
        progenitors = vector<Solution>(epoch.rbegin()+1, epoch.rbegin()+TOP_AMOUNT);
        epoch = vector<Solution>(progenitors);
        epoch.reserve(GENE_POOL_SIZE-TOP_AMOUNT);

        progenitors.push_back(best);
        cout << "  - Best: " << best.getScore() << " with " << best.penalti << " penalti\n";

        // cumulative score for rulette selection
        cum_score = vector<float>();
        cum_score.push_back(progenitors[0].getScore());
        for (size_t i = 1; i< progenitors.size(); ++i){
            cum_score.push_back(cum_score.back() + abs(progenitors[i].getScore()));
        }

        cout << "  - cumulative score: 0-"<<cum_score.back() << " of size " << cum_score.size() << '\n';

        transform_chance = generateProbVector(progenitors.size());

        int select, select2;

        // Crossing over
        while (epoch.size() < GENE_POOL_SIZE-1){
            select = getProgenitor(cum_score);
            while (transform_chance[select] > PC) select = getProgenitor(cum_score);

            select2 = getProgenitor(cum_score);
            while (transform_chance[select2] > PC || select == select2) select2 = getProgenitor(cum_score);

            epoch.push_back(progenitors[select].crossOver(progenitors[select2]));
            epoch.back().eval(weights, nodes, tmax, PENALTI);

            epoch.push_back(progenitors[select2].crossOver(progenitors[select]));
            epoch.back().eval(weights, nodes, tmax, PENALTI);
        }

        // Mutation
        transform_chance = generateProbVector(epoch.size());
        int mut_amount = 0;
        for (size_t i = 0; i < epoch.size(); i++) {
            if (transform_chance[i] < PM){
                epoch[i].mutate(weights, tmax);
                epoch[i].eval(weights, nodes, tmax, PENALTI);
                mut_amount++;
            }
            
        }

        cout << "  - " << mut_amount << " mutations\n";
    }

    sort(epoch.begin(), epoch.end());
    cerr << "BEST SOLUTION: " << epoch.back().getScore() << '\n' << epoch.back() << "Penalti: " << epoch.back().penalti << '\n';
    cout << '\n' << "BEST SOLUTION: " << epoch.back().getScore() << '\n' << epoch.back() << '\n';

    return 0;
}