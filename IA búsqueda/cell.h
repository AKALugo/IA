class Cell;
#ifndef Cell_H_
#define Cell_H_

#include <vector>

class Cell
{
  public:

    ~Cell ();

    void ClearSons (); // Limpiamos el vector de hijos, esto se usa para realizar varias veces el
                       // algoritmo A* sobre la misma matriz.

    void set_Dad (Cell*);
    void set_Son (Cell *);
    void set_Value (const int&);
    void set_XY (std::pair<int, int>&);
    void set_F (double);
    void set_G (double);
    void set_Open (bool);
    void set_Close (bool);

    Cell * get_Dad ();
    Cell * get_Son (int&);
    int get_SizeSons ();
    int get_Value ();
    double get_F ();
    double get_G ();
    bool get_Open ();
    bool get_Close ();
    std::pair<int, int>& get_XY();

  private:
    Cell * dad_ = NULL; // Puntero padre, apunta a la celda que metió a esta celda a openlist de A*.
    std::vector<Cell *> sons_; // Vector de hijos de cada celda.
    std::pair<int, int> xy_; // Coordenadas X Y.
    double f_, g_ = 0;  // F(n) que en nuestro problema es F(n) = g(n) h(n)
    int value_; // Valor de la celda
    bool open_ = false, close_ = false;
};

#endif //Cell_H_