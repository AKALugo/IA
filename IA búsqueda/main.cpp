//sudo apt-get install libncurses5-dev

#include "world.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

int main() {

  int rows, cols, mode, percentage;
  std::string read;
  bool ok;

  std::cout << "Introduzca las dimensiones del mundo (Dimensiones minimas 2x2 y dimensiones máximas 150x150)\n";
  do {
    std::cout << "Filas: ";
    std::cin >> read;

    ok = true;
    for (char caracter : read) 
      if(!std::isdigit(caracter)) ok = false;

    if (ok) rows = std::stoi(read);
  } while (!ok || rows < 2 || rows > 150);


  do {
    std::cout << "Columnas: ";
    std::cin >> read;

    ok = true;
    for (char caracter : read) 
      if(!std::isdigit(caracter)) ok = false;

    if (ok) cols = std::stoi(read);
  } while (!ok || cols < 2 || rows > 150);


  World world(rows, cols);
  Heuristica * h;


  do {
    std::cout << "Introduzca la coordenada de INICIO: ";
    std::cin >> read;

  } while (!world.BuildStart(read));


  do {
    std::cout << "Introduzca la coordenada de FIN: ";
    std::cin >> read;

  } while (!world.BuildEnd(read));


  do {
    std::cout << "Introduzca la forma de definir la posicion de los obstaculos:" << 
                 "\n-0 Manual\n-1 Aleatorio\n-2 Fichero\nModo: ";
    std::cin >> read;

    ok = true;
    for (char caracter : read) 
      if(!std::isdigit(caracter)) ok = false;

    if (ok) mode = std::stoi(read);
  } while (!ok || mode < 0 || mode > 2);


  switch (mode)
  {
  case 0:
    std::cout << "Introduzca las coordenadas separadas por una \",\" .Por ejemplo 3,5.\n"
              << "Si desea terminar de introducir coordenadas escriba \"FIN\".\n";
    do {
      std::cout << "Coordenada:";
      std::cin >> read;
      world.BuildObstacles(read);

    } while (read != "FIN");
    break;
  case 1:
    do {
      std::cout << "Introduzca el % de obstáculos que quiere: ";
      std::cin >> read;

      ok = true;
      for (char caracter : read) 
        if(!std::isdigit(caracter)) ok = false;

      if (ok) percentage = std::stoi(read);
    } while (!ok || percentage < 0 || percentage > 100);

    world.BuildRamdonObstacles(percentage);
    break;
  case 2:

    std::ifstream file;
    do {
      std::cout << "Introduzca el nombre del archivo: ";
      std::cin >> read;
      file.open(read);

      if (!file.is_open())
        std::cout << "ERROR!!!. Ha ocurrido un problema con el archivo, " << 
                   "compruebe le nombre y vuelva a intentarlo\n";
    } while (!file.is_open());

    while (!file.eof()) {
      file >> read;
      world.BuildObstacles(read);
    }
    
    file.close();
    break;
  }
  

  std::cout << "\n----INFORMACION----" << std::endl;
  world.Colors();

  h = new H_Manhattan;

  if (world.AStar(h, false)) printf("%s\nEXITO!!!%s", "\033[0;00;32m", Clear);
  else                       printf("%s\nFRACASO!!!%s", "\033[0;00;31m", Clear);
  world.PrintWorld();
  std::cout << std::endl << "4 DIRECCIONES, HEURISTICA MANHATTAN" << std::endl << std::endl;
  std::cout << "NODOS EXPLORADOS: " << world.explored_cells_ << std::endl;
  std::cout << "NODOS QUE FORMAN PARTE DE LA SOLUCION: " << world.road_ << std::endl;
  std::cout << "TIEMPO DE BUSQUEDA: " << world.search_time() << std::endl << std::endl;
  world.explored_cells_ = 0;
  world.road_ = 0;


  if (world.AStar(h, true)) printf("%sEXITO!!!%s", "\033[0;00;32m", Clear);
  else                      printf("%sFRACASO!!!%s", "\033[0;00;31m", Clear);
  world.PrintWorld();
  std::cout << std::endl << "8 DIRECCIONES, HEURISTICA MANHATTAN" << std::endl << std::endl;
  std::cout << "NODOS EXPLORADOS: " << world.explored_cells_ << std::endl;
  std::cout << "NODOS QUE FORMAN PARTE DE LA SOLUCION: " << world.road_ << std::endl;
  std::cout << "TIEMPO DE BUSQUEDA: " << world.search_time() << std::endl << std::endl;
  world.explored_cells_ = 0;
  world.road_ = 0;

  h = new H_Euclidiana;

  if (world.AStar(h, false)) printf("%sEXITO!!!%s", "\033[0;00;32m", Clear);
  else                       printf("%sFRACASO!!!%s", "\033[0;00;31m", Clear);
  world.PrintWorld();
  std::cout << std::endl << "4 DIRECCIONES, HEURISTICA EUCLIDIANA" << std::endl << std::endl;
  std::cout << "NODOS EXPLORADOS: " << world.explored_cells_ << std::endl;
  std::cout << "NODOS QUE FORMAN PARTE DE LA SOLUCION: " << world.road_ << std::endl;
  std::cout << "TIEMPO DE BUSQUEDA: " << world.search_time() << std::endl << std::endl;
  world.explored_cells_ = 0;
  world.road_ = 0;


  if (world.AStar(h, true)) printf("%sEXITO!!!%s", "\033[0;00;32m", Clear);
  else                       printf("%sFRACASO!!!%s", "\033[0;00;31m", Clear);
  world.PrintWorld();
  std::cout << std::endl << "8 DIRECCIONES, HEURISTICA EUCLIDIANA" << std::endl << std::endl;
  std::cout << "NODOS EXPLORADOS: " << world.explored_cells_ << std::endl;
  std::cout << "NODOS QUE FORMAN PARTE DE LA SOLUCION: " << world.road_ << std::endl;
  std::cout << "TIEMPO DE BUSQUEDA: " << world.search_time() << std::endl << std::endl;
  world.explored_cells_ = 0;
  world.road_ = 0;

  h = new H_Distancia_Tchebysev;

  if (world.AStar(h, false)) printf("%sEXITO!!!%s", "\033[0;00;32m", Clear);
  else                       printf("%sFRACASO!!!%s", "\033[0;00;31m", Clear);
  world.PrintWorld();
  std::cout << std::endl << "4 DIRECCIONES, HEURISTICA DISTANCIA TCHEBYSEV" << std::endl << std::endl;
  std::cout << "NODOS EXPLORADOS: " << world.explored_cells_ << std::endl;
  std::cout << "NODOS QUE FORMAN PARTE DE LA SOLUCION: " << world.road_ << std::endl;
  std::cout << "TIEMPO DE BUSQUEDA: " << world.search_time() << std::endl << std::endl;
  world.explored_cells_ = 0;
  world.road_ = 0;


  if (world.AStar(h, true)) printf("%sEXITO!!!%s", "\033[0;00;32m", Clear);
  else                       printf("%sFRACASO!!!%s", "\033[0;00;31m", Clear);
  world.PrintWorld();
  std::cout << std::endl << "8 DIRECCIONES, HEURISTICA DISTANCIA TCHEBYSEV" << std::endl << std::endl;
  std::cout << "NODOS EXPLORADOS: " << world.explored_cells_ << std::endl;
  std::cout << "NODOS QUE FORMAN PARTE DE LA SOLUCION: " << world.road_ << std::endl;
  std::cout << "TIEMPO DE BUSQUEDA: " << world.search_time() << std::endl << std::endl;
  world.explored_cells_ = 0;
  world.road_ = 0;
}