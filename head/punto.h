#include <iostream>

class Punto {
    public:
        float x, y;
        int score;
        Punto(float newX, float newY, int newScore);
        friend std::ostream &operator<<(std::ostream &out, const Punto &pto);
};

float eucDist(Punto pto1, Punto pto2);