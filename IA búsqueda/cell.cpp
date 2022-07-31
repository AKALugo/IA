#include "cell.h"

Cell::~Cell () {
  delete dad_;
  dad_ = NULL;
}



void 
Cell::ClearSons () {

  sons_.clear();
}



void 
Cell::set_Dad (Cell* a) {
  
  dad_ = a;
}



void
Cell::set_F (double a) {

  f_ = a;
}



void
Cell::set_G (double a) {

  g_ = a;
}



void 
Cell::set_Son (Cell * a) {

  sons_.push_back(a);
}



void 
Cell::set_Value(const int& a) {

  value_ = a;
}



void 
Cell::set_XY(std::pair<int, int>& a) {

  xy_ = a;
}



void
Cell::set_Open(bool a) {

  open_ = a;
}



void
Cell::set_Close(bool a) {

  close_ = a;
}



Cell * 
Cell::get_Dad () {

  return dad_;
}



Cell *
Cell::get_Son (int& a) {

  return sons_[a];
}



int
Cell::get_SizeSons () {

  return sons_.size();
}



int
Cell::get_Value () {

  return value_;
}



std::pair<int, int>&
Cell::get_XY() {

  return xy_;
}



double
Cell::get_F () {
  
  return f_;
}



double
Cell::get_G () {
  
  return g_;
}



bool
Cell::get_Open () {
  
  return open_;
}



bool
Cell::get_Close () {
  
  return close_;
}