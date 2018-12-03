#include "node.h"
#include <iostream>
#include <math.h>

Node::Node(float newX, float newY, int newScore){
    x = newX;
    y = newY;
    score = newScore;
}

std::ostream& operator<< (std::ostream &out, Node const& pto) {
    out << "(" << pto.x << ", " << pto.y << ") " << pto.score << '\n';
    return out;
}


float eucDist(Node pto1, Node pto2){
    return sqrtf(pow(pto1.x - pto2.x, 2) + pow(pto1.y - pto2.y, 2));
}