#ifndef ROUTE_CLASS
#define ROUTE_CLASS
#include <vector>
#include <iostream>
#include "node.h"
using namespace std;

typedef vector<int> route;
typedef vector<route> cromosome;

class Route {
    private:
        unsigned int n;
        vector<int> seq;

    public:
        Route(int nn, bool populate);
        void append(int elem);
        float totalDistance(vector <vector <float>> &weights);
        int totalScore(vector<Node> &nodes);
        void generateInitial();
        friend std::ostream &operator<<(std::ostream &out, const Route &ruta);
};
#endif