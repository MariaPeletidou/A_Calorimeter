#include <iostream>
#include"Point.hh"
#include"Calorimeter.hh"
#include"CaloGrid.hh"
#include"CaloCell.hh"
#include"CaloReader.hh"
#include"CaloReaderException.hh"
#include<string>
#include"CaloReco.hh"

using namespace std;

int main() {
	
	try {
    CaloReader one("calo.dat");
}
	catch (CaloReaderException excep){
		cout << excep.what() << endl;
		return 0;
	}
	
	CaloReader r("calo.dat");
	CaloReader* reader=&r;
	r.calo().dumpReadoutMap();

	while (reader->readEvent()) {//The file contains two events so there will be printed two matrices with elements with different energies. 
       reader->calo().dumpEvent();

	   CaloReco test(reader->calo());//Test of the CaloReco
	   test.findClusters();

	   cout << reader->calo().grid().cell(6, 1)->energy() << endl;
	   cout << reader->calo().grid().cell(6, 1)->getclusterID() << endl;//In the first loop of readevent the cell has zero energy while in the second loop it has energy>0 so it 
	   //belongs to a cluster
	   cout << reader->calo().grid().cell(2,8)->energy() << endl;
	   cout << reader->calo().grid().cell(2,8)->getclusterID() << endl;//In the first loop of readevent the cell has zero energy while in the second loop it has energy>0 so it 
	   //belongs to a cluster

	   cout << reader->calo().grid().cell(7, 6)->energy() << endl;
	   cout << reader->calo().grid().cell(7, 6)->getclusterID() << endl;//In the first loop of readevent the cell has energy while in the second loop it has energy==0
	}
	
	
	return 0;
}
