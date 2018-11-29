#ifndef ROUTE_CLASS
#define ROUTE_CLASS
#include <vector>
#include <iostream>
#include "punto.h"
using namespace std;

typedef vector<int> route;
typedef vector<route> cromosome;

class Route {
    private:
    unsigned int n;
    vector<int> seq;

    public:
    Route(int nn);
    void append(int elem);
    float totalDistance(vector <vector <float>> weights);
    int totalScore(vector<Punto> nodes);
    void generateInitial();
    friend std::ostream &operator<<(std::ostream &out, const Route &ruta);
};
#endif