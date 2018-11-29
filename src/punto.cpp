#include "punto.h"
#include <iostream>
#include <math.h>

Punto::Punto(float newX, float newY, int newScore){
    x = newX;
    y = newY;
    score = newScore;
}

std::ostream& operator<< (std::ostream &out, Punto const& pto) {
    out << "(" << pto.x << ", " << pto.y << ") " << pto.score << '\n';
    return out;
}


float eucDist(Punto pto1, Punto pto2){
    return sqrtf(pow(pto1.x - pto2.x, 2) + pow(pto1.y - pto2.y, 2));
}