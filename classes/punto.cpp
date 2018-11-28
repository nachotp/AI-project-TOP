#include "punto.h"
#include <iostream>

Punto::Punto(float newX, float newY){
    x = newX;
    y = newY;
}

std::ostream& operator<< (std::ostream &out, Punto const& pto) {
    out << "(" << pto.x << ", " << pto.y << ")";
    return out;
}