class World;
#ifndef World_H_
#define World_H_

#include "cell.h"
#include "heuristica.hpp"

#include <assert.h>

#include <iostream>
#include <list>
#include <vector>

// https://elpuig.xeill.net/Members/vcarceler/articulos/escape-ansi
#define Green "\033[0;42;32m"
#define Red "\033[0;41;31m"
#define White "\033[0;1;47;1;37m"
#define Clear "\033[0m"
#define Blue "\033[0;44;34m"
#define Cyan "\033[0;46;36m"
#define DGray "\033[0;1;40;1;30m"

enum State {FREE, OBSTACLE, PASSED, START, END, MARK};


class World {

 public:
  World(const int& rows, const int& cols);

  void ChangeCellState(const int& i, const int& j, const int& state); // Cambia el valor de una celda.

  bool BuildPosicion (std::string& number, const int value); //Pasandole unas coordenadas cambia el valor de una celda.
  void BuildObstacles (std::string& number); //Invoca a BuildPosicion y le valor OBSTACLE a la celda.
  bool BuildStart (std::string& number); //Invoca a BuildPosicion y le valor START a la celda.
  bool BuildEnd (std::string& number); //Invoca a BuildPosicion y le valor END a la celda.
  void BuildRamdonObstacles (int& percentage); // Genera obstaculos de forma aleatoria.

  void PrintCell(const int& i, const int& j); // Imprime una celda.
  void PrintWorld();  // Imprime la matriz usando a PrintCell.

  int get_CellState(const int& i, const int& j); // Devuelve el estado de la celda.
  int get_Rows(void); // Devuelve las filas.
  int get_Cols(void); // Devuelve las columnas.

  void MakeSons (int, int, bool); // Crea los hijos de la coordenada pasada por parametros
  void MakeRoad (Cell *); // Marca las celdas recorridas hasta la celda objetivo

  void Colors (); // Imprime el codigo de colores.
  bool AStar (Heuristica * h, bool eigth); // Algoritmo que usando la heuristica encuetra la solucion.

  double search_time(void);
  std::string time_(void);
  int explored_cells_ = 0;
  int road_ = 0;

 private:
  std::vector<std::vector<Cell *>> world_; // Matriz.
  Cell * end_; // * a celda objetivo.
  Cell * start_; // * a celda inicial.

  int rows_; // Filas.
  int cols_; // Columnas.
  long double search_time_;
};




#endif //World_H_