#ifndef CALORIMETER_HH
#define CALORIMETER_HH

#include "CaloGrid.hh"
#include "Point.hh"
#include <iomanip> 
class Calorimeter {
public:

  Calorimeter(int sizex, int sizey, Point position=Point(0,0,0)) : 
    _grid(sizex,sizey), _pos(position)
  {}

  CaloGrid& grid() { return _grid ; }

  const CaloGrid& grid() const { return _grid ; }
  Point& position() { return _pos ; }
  const Point& position() const { return _pos ; }

  CaloCell* findCellByID(int id) {
      int i=0, j=0;
      while (_grid.cell(i, j) != 0) {//The function cell() returns a null pointer when we ask for a cell that is off the length. Also every time that we determine a CaloGrid object
          //every pointer array that is inside the length is not null as we have by default set the energy=0 and the ID=0 in the CaloCell so it points somewhere. 
          //So we can use the function cell to determine the sizex and sizey of the grid.
          while (_grid.cell(i, j) != 0) {
              if (_grid.cell(i, j)->readoutID() == id) {
                  return _grid.cell(i, j); 
              }
           j++;
          }
       i++;
       j = 0;//we set i++ and j=0 to go to the next line of the matrix i.e (a+1,0),(a+1,1)...(a+1,sizey).
      }
      return 0;//Returns null pointer if there is no cell with that ID
  }
  
  void clear() {
      int i = 0, j = 0;
      while (_grid.cell(i, j) != 0) {//We use the same loop as in function findCellByID() to determine whether we are outside of the lenght of the grid.
          while (_grid.cell(i, j) != 0) {
              _grid.cell(i, j)->setEnergy(0);
              j++;
          }
          i++;
          j = 0;
      }
  }
  
  void dumpReadoutMap(std::ostream& os = std::cout) const {
      int i = 0, j = 0;
      while (_grid.cell(i, j) != 0) {//We use the same loop as in function findCellByID() to determine whether we are outside of the lenght of the grid.
          while (_grid.cell(i, j) != 0) {
              os << setw(10) << _grid.cell(i, j)->readoutID();
              j++;
          }
          i++;
          j = 0;
          os << endl;
      }
      os << endl;
  }
          
              
  void dumpEvent(std::ostream& os = cout) {
      int i = 0, j = 0;
      while (_grid.cell(i, j) != 0) {//We use the same loop as in function findCellByID() to determine whether we are outside of the lenght of the grid.
          while (_grid.cell(i, j) != 0) {
              if (_grid.cell(i, j)->energy() < 0.5) {
                  os << setw(10) << ".";
              }
              else if (_grid.cell(i, j)->energy() >= 0.5 && _grid.cell(i, j)->energy() <= 2.0) {
                  os << setw(10) << "x";
              }
              else {
                  os << setw(10) << "X";
              }
              j++;
          }
          i++;
          j = 0;
          os << endl;
      }
      os << endl;
  }

private:
  CaloGrid _grid ;
  Point _pos ;


} ;

#endif 
