class Heuristica;
#ifndef Heuristica_H_
#define Heuristica_H_

#include <cmath>

class Heuristica {

  public:
    virtual double operator()(std::pair<int, int> & v1, std::pair<int, int> & v2) = 0;
};



class H_Manhattan: public Heuristica {

  public:
    virtual double operator()(std::pair<int, int> & v1, std::pair<int, int> & v2) {
      
      return abs(v1.first - v2.first) + abs(v1.second - v2.second);
    }
};



class H_Euclidiana: public Heuristica {

  public:
    virtual double operator()(std::pair<int, int> & v1, std::pair<int, int> & v2) {

      return sqrt(pow(v1.first - v2.first, 2) + pow(v1.second - v2.second, 2));
    }
};

class H_Distancia_Tchebysev: public Heuristica {

  public:
    virtual double operator()(std::pair<int, int> & v1, std::pair<int, int> & v2) {

      return std::max((abs(v1.first - v2.first)),(abs(v1.second - v2.second)) );
    }
};
#endif // Heuristica_H_;