#ifndef CALOREADEREXCEPTION_HH
#define CALOREADEREXCEPTION_HH
#include"Calorimeter.hh"
#include<fstream>
#include<string>

class CaloReaderException {
public:
	CaloReaderException(const char* name ) :_what(name) {};

	const char* what() {return  _what.c_str(); }

private:
	string _what;
};



#endif
