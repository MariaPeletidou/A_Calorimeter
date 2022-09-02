#ifndef CALOREADER_HH
#define CALOREADER_HH
#include"Calorimeter.hh"
#include<fstream>
#include<string>
#include"CaloReaderException.hh"


class CaloReader {
public:
	CaloReader(const char* filename):_calo(0),_file(filename) {
		if (_file.fail()) {throw CaloReaderException("Error file could not open correctly"); }
		_file >> word;
		if (word != "BEGIN_CALO_DEF") { throw CaloReaderException("Error the file isn't structured correctly"); }
		_file >> word;
		if (word != "SIZE") { throw CaloReaderException("Error the file isn't structured correctly"); }
		_file >> size_x;
		_file >> size_y;
		_calo = new Calorimeter(size_x, size_y);
		_file >> word;
		while (word == "POSITION") {
			_file >> readoutID;
			_file >> ix;
			_file >> iy;
			_calo->grid().cell(ix, iy)->setReadoutID(readoutID);
			_file >> word;
		}
		if (word != "END_CALO_DEF") { throw CaloReaderException("Error the file isn't structured correctly"); }//We just checking that the final word is END_CALO_DEF.
	}

	//~CaloReader();

	//Accesor
	Calorimeter& calo() { return *_calo; }

	bool readEvent() {
		if (_file.fail()) { return false; }
		_calo->clear();//set energies to zero.
		_file >> word;
		if (word != "BEGIN_EVENT") { return false; }
		_file >> word;
		if (word != "ENERGY") { return false; }
		while (word == "ENERGY") {
        _file >> readoutID;
		_file >> energy;
		_file >> word;
		_calo->findCellByID(readoutID)->setEnergy(energy);
		}
		if (word != "END_EVENT") { return false; }
		return true;
	}
	

private:
	double energy=0;
	int size_x, size_y;
	string word = " ";
	int readoutID=0, ix=0, iy=0;
	Calorimeter* _calo;
	ifstream _file;

};





#endif
