#include <iostream>

class Punto {
    public:
        float x, y;
        Punto::Punto(float newX, float newY);
        std::ostream& operator<< (std::ostream &out, Punto const& pto);

}
