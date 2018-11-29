#include "punto.h"
#include <iostream>

Punto::Punto(float newX, float newY, int newScore){
    x = newX;
    y = newY;
    score = newScore;
}

std::ostream& operator<< (std::ostream &out, Punto const& pto) {
    out << "(" << pto.x << ", " << pto.y << ") " << pto.score << '\n';
    return out;
}
