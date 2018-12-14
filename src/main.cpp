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


    // Generar matriz de distancias aplicando distancia euclidiana y almacenando el valor en ambas direcciones.
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

    // Generar GENE_POOL_SIZE soluciones completamente aleatorias y almacenar su puntaje el cual queda almacenado en el objeto solución.
    for (size_t i = 0; i < GENE_POOL_SIZE; i++){
        epoch.push_back(Solution(n, m));
        epoch[i].eval(weights, nodes, tmax, PENALTI);
    }

    // Proceso de evolución que se repetirá MAX_GENERATIONS veces.
    for(size_t gen = 0; gen < MAX_GENERATIONS; ++gen){
        // Ordenar soluciones para poder realizar elitismo
        sort(epoch.begin(), epoch.end());

        // Almacenar la mejor solución hasta la generación actual para asegurar que el algoritmo no baje de calidad.
        if (gen == 0 || best < epoch.back()) best = epoch.back();

        // Seleccionar las TOP_AMOUNT soluciones con mayor puntaje.
        progenitors = vector<Solution>(epoch.rbegin()+1, epoch.rbegin()+TOP_AMOUNT);
        epoch = vector<Solution>(progenitors);
        epoch.reserve(GENE_POOL_SIZE-TOP_AMOUNT);

        progenitors.push_back(best);

        // Generar arreglo con el puntaje acumulado de soluciones, así se tienen rangos que permiten aplicar la selección por ruleta
        // Mejores soluciones tienen un rango más amplio.
        accum_score = vector<double>();
        accum_score.push_back(progenitors[0].getScore());
        for (size_t i = 1; i< progenitors.size(); ++i){
            accum_score.push_back(accum_score.back() + abs(progenitors[i].getScore()));
        }

        // Generar números aleatorios entre 0 y 1 para cada una de las soluciones progenitoras
        transform_chance = generateProbVector(progenitors.size());

        int select, select2;

        // Crossing over hasta llenar la generación.
        while (epoch.size() < GENE_POOL_SIZE-1){
            // Se aplica busqueda binaria por bisección para encontrar el intervalo donde se encuentra una solución
            // Aplicando así la selección por ruleta.
            select = getProgenitor(accum_score);
            while (transform_chance[select] > PC) select = getProgenitor(accum_score);

            select2 = getProgenitor(accum_score);
            while (transform_chance[select2] > PC || select == select2) select2 = getProgenitor(accum_score);

            // Se generan 2 soluciones apliclando el cruze de intercambios de rutas y se evaluán cada una

            epoch.push_back(progenitors[select].crossOver(progenitors[select2]));
            epoch.back().eval(weights, nodes, tmax, PENALTI);

            epoch.push_back(progenitors[select2].crossOver(progenitors[select]));
            epoch.back().eval(weights, nodes, tmax, PENALTI);
        }

        // Para diversificar, se aplican mutadores según la probabilidad, se aplica solo un mutador máximo por solución.
        // Estos pueden dversificar, reparar o mejorar soluciones.
        // Se vuelven a evaluar las soluciones mutadas.
        transform_chance = generateProbVector(epoch.size());
        for (size_t i = 0; i < epoch.size(); i++) {
            if (transform_chance[i] < PM){
                epoch[i].mutate(weights, tmax);
                epoch[i].eval(weights, nodes, tmax, PENALTI);
            }
            
        }

        // Para completar las GENE_POOL_SIZE se agrega la mejor solución global mutada para promover
        // el encuentro de soluciones interesantes.
        epoch.push_back(best);
        epoch.back().mutate(weights, tmax);
        epoch.back().eval(weights, nodes, tmax, PENALTI);
    }

    // Se selecciona la mejor solución de todas y es entregada.
    sort(epoch.begin(), epoch.end());

    cout << epoch.back().getScore() << '\n' << epoch.back();

    return 0;
}