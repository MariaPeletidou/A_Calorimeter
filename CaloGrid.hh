#ifndef CALOGRID_HH
#define CALOGRID_HH

#include "CaloCell.hh"
#include <iostream>
using namespace std ;

class CaloGrid {
public:

  CaloGrid(int size_x, int size_y) : _nx(size_x), _ny(size_y) {
    _array = new CaloCell[_nx*_ny] ;
  }

  CaloGrid(const CaloGrid& other) : _nx(other._nx), _ny(other._ny) {
    _array = new CaloCell[_nx*_ny] ;
    for(int i = 0 ; i<_nx*_ny ; i++) {
      _array[i] = other._array[i] ;
    }
  }

  ~CaloGrid() {
    delete[] _array ;
  }
  
  const CaloCell* cell(int x, int y) const { 
    return const_cast<CaloGrid*>(this)->cell(x,y) ; 
  }
  
  CaloCell* cell(int x, int y) {
    if (x<0 || x>=_nx || y<0 || y>=_ny) return 0 ;
    return _array + x*_ny + y ;
  }
  

private:

  int _nx ;
  int _ny ;
  CaloCell* _array ;

} ;

#endif 
