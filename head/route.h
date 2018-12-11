#ifndef ROUTE_CLASS
#define ROUTE_CLASS
#include <vector>
#include <iostream>
#include "node.h"
using namespace std;

typedef vector<int> route;

class Route {
    private:
        unsigned int n;
        route seq;

    public:
        float roundtime;
        
        Route(int nn, bool populate);
        void append(int elem);
        float totalDistance(vector<vector<float>> &weights);
        void markVisit(vector<bool> &visited);
        int totalScore(vector<Node> &nodes);
        int size();
        void flipSeq(int from, int to);
        void generateInitial();
        friend std::ostream &operator<<(std::ostream &out, const Route &ruta);
};
#endif