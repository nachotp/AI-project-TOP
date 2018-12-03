#ifndef NODE_CLASS
#define NODE_CLASS
#include <iostream>

class Node {
    public:
        float x, y;
        int score;
        Node(float newX, float newY, int newScore);
        friend std::ostream &operator<<(std::ostream &out, const Node &pto);
};

float eucDist(Node pto1, Node pto2);
#endif