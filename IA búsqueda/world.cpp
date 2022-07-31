#include "world.hpp"

World::World(const int& rows, const int& cols) {
  rows_ = rows;
  cols_ = cols;

  world_.resize(rows);
  for (int i = 0; i < rows; i++) {
    world_[i].resize(cols);
  }
  // Inicializamos el tablero paraque este todo blanco
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Cell * aux = new Cell;
      aux->set_Value(FREE);
      std::pair<int, int> pair {i, j};
      aux->set_XY(pair);
      world_[i][j] = aux;
    }
  }
}



void World::MakeSons (int x, int y, bool eigth) {

  world_[x][y]->ClearSons();
      
  if (x - 1 >= 0 && world_[x -1][y]->get_Value() != OBSTACLE) 
    world_[x][y]->set_Son(world_[x -1][y]);
  if (y - 1 >= 0 && world_[x][y - 1]->get_Value() != OBSTACLE) 
    world_[x][y]->set_Son(world_[x][y -1]);
  if (x + 1 < rows_ && world_[x +1][y]->get_Value() != OBSTACLE) 
    world_[x][y]->set_Son(world_[x +1][y]);
  if (y + 1 < cols_ && world_[x][y + 1]->get_Value() != OBSTACLE) 
    world_[x][y]->set_Son(world_[x][y + 1]);

  if (eigth) {
    if (x - 1 >= 0 && y - 1 >= 0 && world_[x -1][y -1]->get_Value() != OBSTACLE) 
      world_[x][y]->set_Son(world_[x -1][y -1]);
    if (x + 1 < rows_ && y + 1 < cols_ && world_[x + 1][y + 1]->get_Value() != OBSTACLE) 
      world_[x][y]->set_Son(world_[x +1][y +1]);
    if (x - 1 >= 0 && y + 1 < cols_ && world_[x -1][y +1]->get_Value() != OBSTACLE) 
      world_[x][y]->set_Son(world_[x -1][y +1]);
    if (x + 1 < rows_ && y - 1 >= 0 && world_[x +1][y -1]->get_Value() != OBSTACLE) 
      world_[x][y]->set_Son(world_[x +1][y -1]);
  }
}



// Comprueba que las coordenadas leidas tengan el formato adecuado y controla errores.
bool
World::BuildPosicion (std::string& number, const int value) {

  try {
    if (number != "FIN") {
      std::string number1, number2;
      int part = 0;

      for (char caracter : number) {
        if (part == 0 && caracter != ',' && caracter != '(')
          number1.push_back(caracter);
        if (part == 1 && caracter != ')')
          number2.push_back(caracter);
        if (caracter == ',')
          part++;
      }

      if (number1.empty() || number2.empty()) throw 0;

      for (char caracter : number1)
        if (!std::isdigit(caracter)) throw 0;
      
      for (char caracter : number2)
        if (!std::isdigit(caracter)) throw 0;

      int i = std::stoi(number1), j = std::stoi(number2);

      if (i < 0 || i >= rows_ || j < 0 || j >= cols_) throw 1;

      if (world_[i][j]->get_Value() == OBSTACLE) throw 2;
      else if (world_[i][j]->get_Value() == START) throw 3;
      else if (world_[i][j]->get_Value() == END) throw 4;
      else {
        world_[i][j]->set_Value(value);
        if (value == END) end_ = world_[i][j];
        if (value == START) start_ = world_[i][j];
        return true;
      }
      return false;
    }
  }
  catch (int& ex) {

    std::cout << "ERROR!!!. ";
    switch (ex)
    {
    case 0:
      std::cout << "EL FORMATO DE LA COORDENADA " << number << " ES INCORRECTO.\n";
      break;
    case 1:
      std::cout << "LA COORDENADA " << number << " SE SALE DE NUESTRO MUNDO.\n";
      break;
    case 2:
      std::cout << "YA HABÍA UN OBSTÁCULO EN LA COORDENADA " << number << ".\n";
      break;
    case 3:
      std::cout << "EN LA COORDENADA " << number << " SE ENCUENTRA LA CASILLA DE INICIO.\n";
      break;
    case 4:
      std::cout << "EN LA COORDENADA " << number << " SE ENCUENTRA LA CASILLA DE FIN.\n";
      break;
    }
  }
  return false;
}



bool
World::BuildStart (std::string& number) {

  return BuildPosicion (number, START);
}



bool
World::BuildEnd (std::string& number) {

  return BuildPosicion (number, END);
}



void
World::BuildObstacles(std::string& number) {

  BuildPosicion (number, OBSTACLE);
}



void 
World::BuildRamdonObstacles (int& percentage) {

  srand(time(0));
  int total = rows_ * cols_;
  int ramdon = total * percentage / 100;
  if (total * percentage % 100 != 0) ramdon++;

  if (ramdon == rows_ * cols_ ) ramdon = ramdon -2;
  else if (ramdon == rows_ * cols_ - 1) ramdon = ramdon -1;

  int number;
  while (ramdon != 0) {

    number = rand()%total;
    if (world_[number / cols_][number % cols_]->get_Value() != OBSTACLE && 
        world_[number / cols_][number % cols_]->get_Value() != START &&
        world_[number / cols_][number % cols_]->get_Value() != END) {
      world_[number / cols_][number % cols_]->set_Value(OBSTACLE);
      ramdon--;
    }
  }
}



bool
World::AStar (Heuristica * h, bool eigth) {

  // EMPEZAR TEMPORIZADOR
  clock_t t0 = clock();
  // Creamos lista de punteros
  std::list<Cell *> open_list, close_list;

  // Establecemos F(n) de la casilla de inicio;
  start_->set_F((*h)(start_->get_XY(), end_->get_XY()));

  // Metemos a start_ en la openlist.
  open_list.push_front(start_);

  while (!open_list.empty()) {

    // Recorremos la lista buscando a la celda con menor F(n).
    std::list<Cell *>::iterator min_XY = open_list.begin(), it;
      for (it = min_XY; it != open_list.end(); it++)
        if ((*it)->get_F() < (*min_XY)->get_F())
          min_XY = it;

    Cell * aux =  *(min_XY);
    if (aux->get_Value() != END && aux->get_Value() != START) aux->set_Value(MARK);

    // Si la celda seleccionada es el objetivo acabamos.
    if (aux == end_) {
      // Marcamos todas las celdas parte de la solucion.
      MakeRoad(aux);
      // PARAR TIEMPO
      search_time_ = (long double)(clock() - t0);
      return true;
    }

    aux->set_Close(true);
    aux->set_Open(false);
    // Si la celda no es el objetivo la eliminamos de la lista y generamos sus hijos.
    close_list.push_front(aux);
    explored_cells_++;
    // Guaradamos el puntero en close_list ya que ha sido explorado
    open_list.erase(min_XY);

    // Generamos los hijos de la celda a analizar
    MakeSons(aux->get_XY().first, aux->get_XY().second, eigth);

    // Recorremos todos los hijos
    for (auto i = 0; i < aux->get_SizeSons(); i++) {

      // Si estaba en open_list y ahora su g(n) es menor actualizamos valor y actualizamos nodo padre
      if (aux->get_Son(i)->get_Open() && aux->get_Son(i)->get_G() > (aux->get_G() + 1)) {
        aux->get_Son(i)->set_Dad(aux);
        aux->get_Son(i)->set_G(aux->get_G() + 1);
        aux->get_Son(i)->set_F((*h)(aux->get_Son(i)->get_XY(), end_->get_XY()) + aux->get_Son(i)->get_G());
      }

      // Si estaba en close_list y ahora su g(n) actualizamos valor, nodo padre, lo eliminamos de close_list y lo añadimso a open_list
      if (aux->get_Son(i)->get_Close() && aux->get_Son(i)->get_G() > (aux->get_G() + 1))
        for (std::list<Cell *>::iterator at = close_list.begin(); at != close_list.end(); at++) 
          if ((*at)->get_XY() ==  aux->get_Son(i)->get_XY()) {
            aux->get_Son(i)->set_Close(false);
            aux->get_Son(i)->set_Open(true);
            aux->get_Son(i)->set_Dad(aux);
            aux->get_Son(i)->set_G(aux->get_G() + 1);
            aux->get_Son(i)->set_F((*h)(aux->get_Son(i)->get_XY(), end_->get_XY()) + aux->get_Son(i)->get_G());
            open_list.push_front(aux->get_Son(i));
            close_list.erase(at);
            break;
          }

      // Si no estaba ni en open_list ni en close_list lo añadimos a open_list y le establecemos unos valores.
      if (!aux->get_Son(i)->get_Open() && !aux->get_Son(i)->get_Close()) {
        aux->get_Son(i)->set_Open(true);
        aux->get_Son(i)->set_Dad(aux);
        aux->get_Son(i)->set_G(aux->get_G() + 1);
        aux->get_Son(i)->set_F((*h)(aux->get_Son(i)->get_XY(), end_->get_XY()) + aux->get_Son(i)->get_G());
        open_list.push_front(aux->get_Son(i));
      }
    }
  }
  // PARAR TIEMPO
  search_time_ = (long double)(clock() - t0);
  return false;
}



void
World::MakeRoad (Cell * a) {

  a = a->get_Dad();
  road_ ++;

  while (a->get_Dad() != NULL) {
    road_ ++;
    a->set_Value(PASSED);
    a = a->get_Dad();
  }
}



void
World::ChangeCellState(const int& i, const int& j, const int& state) {
  world_[i][j]->set_Value(state);
}



void
World::PrintCell(const int& i, const int& j) {

  world_[i][j]->set_Dad(NULL);
  world_[i][j]->set_Open(false);
  world_[i][j]->set_Close(false);

  switch (get_CellState(i,j)) {
    case FREE:
      printf("%s  %s", White, Clear);
      break;
    case OBSTACLE:
      printf("%s  %s", Red, Clear);
      break;
    case PASSED:
      world_[i][j]->set_Value(FREE);
      printf("%s  %s", Green, Clear);
      break;
    case START:
      printf("%s  %s", Cyan, Clear);
      break;
    case END:
      printf("%s  %s", Blue, Clear);
      break;
    case MARK:
      world_[i][j]->set_Value(FREE);
      printf("%s  %s", DGray, Clear);
      break;
  }
}



void
World::PrintWorld() {

  for (int i = 0; i < rows_; i++) {
    std::cout << "\n";
    for (int j = 0; j < cols_; j++) {
      PrintCell(i,j);
    }
  }
}



void
World::Colors () {

  printf("Celda libre: %s  %s\n", White, Clear);
  printf("Celda con opstáculo: %s  %s\n", Red, Clear);
  printf("Celda con camino: %s  %s\n", Green, Clear);
  printf("Celda de inicio: %s  %s\n", Cyan, Clear);
  printf("Celda de fin: %s  %s\n", Blue, Clear);
  printf("Celda recorrida en A*: %s  %s\n", DGray, Clear);
}



int
World::get_CellState(const int& i, const int& j) {
  return world_[i][j]->get_Value();
}



int
World::get_Cols(void) {
  return cols_;
}



int
World::get_Rows(void) {
  return rows_;
}

std::string World::time_(void) {
  return std::string();
}

double World::search_time(void) {
  return search_time_ / CLOCKS_PER_SEC;
}