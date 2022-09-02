#ifndef CALORECO_HH
#define CALORECO_HH
#include"Calorimeter.hh"
#include"CaloGrid.hh"
#include"Calorimeter.hh"
#include "CaloCell.hh"

class CaloReco {
public:
	CaloReco(Calorimeter& Calo):obj(&Calo) {};

	CaloCell* findSeed() {
        int i = 0, j = 0;
        int loop = 0;
        CaloCell* Calo = new CaloCell(0, 0);//We create a CaloCell to keep the cell with the highest energy
        while (obj->grid().cell(i, j) != 0) {
            while (obj->grid().cell(i, j) != 0) {
                if (obj->grid().cell(i, j)->energy()>Calo->energy() && obj->grid().cell(i, j)->getclusterID() == 0) {
                    Calo = obj->grid().cell(i, j);
                    _i = i;//We keep the coordinates of the cell with the highest energy
                    _j = j;
                    loop++;
                }
                j++;
            }
            i++;
            j = 0;
        }
        if (loop==0) { return 0; }//If there are no cells with energy>0 which don't belong to a cluster the function will return a null pointer

        return Calo;
	}

    void findClusters() {
        int i = 0, j = 0;
        while (obj->grid().cell(i, j) != 0) {
            while (obj->grid().cell(i, j) != 0) { 
                    obj->grid().cell(i, j)->setclusterID(0);
                    
            j++;
            }
            i++;
            j = 0;
        }
        clusterid = 1;
        while (findSeed() != 0) {//findSeed returns a null pointer if there are no more cells with energy>0 that don't belong in a cluster.
         growCluster(_i, _j, clusterid);
         clusterid++;//We create clusters starting with the zero one cluster until there is no more cells with energy>0 that don't belong to a cluster
        }
        

    }

    void growCluster(int ix, int iy, int clusid) {
        obj->grid().cell(ix, iy)->setclusterID(clusid);

        if (obj->grid().cell(ix+1,iy)!=0 && obj->grid().cell(ix + 1, iy)->getclusterID() == 0 && obj->grid().cell(ix + 1, iy)->energy() > 0) {//First argument makes sure that there exist the 
            //adjacent cell. Second argument makes sure that the adjacent cell doesn't belong to a cluster. Third argument make sure that the cell has energy>0.
            growCluster(ix + 1, iy, clusid);
        }
        if (obj->grid().cell(ix, iy+1) != 0 && obj->grid().cell(ix , iy+1)->getclusterID() == 0 && obj->grid().cell(ix , iy+1)->energy() > 0) {
            growCluster(ix , iy+1, clusid);
        }
        if (obj->grid().cell(ix + 1, iy+1) != 0 && obj->grid().cell(ix + 1, iy+1)->getclusterID() == 0 && obj->grid().cell(ix + 1, iy+1)->energy() > 0) {
            growCluster(ix + 1, iy+1, clusid);
        }
        if (obj->grid().cell(ix - 1, iy) != 0 && obj->grid().cell(ix -1, iy)->getclusterID() == 0 && obj->grid().cell(ix -1, iy)->energy() > 0) {
            growCluster(ix - 1, iy, clusid);
        }
        if (obj->grid().cell(ix, iy-1) != 0 && obj->grid().cell(ix, iy-1)->getclusterID() == 0 && obj->grid().cell(ix , iy-1)->energy() > 0) {
            growCluster(ix, iy-1, clusid);
        }
        if (obj->grid().cell(ix - 1, iy-1) != 0 && obj->grid().cell(ix - 1, iy-1)->getclusterID() == 0 && obj->grid().cell(ix - 1, iy-1)->energy() > 0) {
            growCluster(ix - 1, iy-1, clusid);
        }
        if (obj->grid().cell(ix + 1, iy-1) != 0 && obj->grid().cell(ix + 1, iy-1)->getclusterID() == 0 && obj->grid().cell(ix + 1, iy-1)->energy() > 0) {
            growCluster(ix + 1, iy-1, clusid);
        }
        if (obj->grid().cell(ix - 1, iy+1) != 0 && obj->grid().cell(ix - 1, iy+1)->getclusterID() == 0 && obj->grid().cell(ix - 1, iy+1)->energy() > 0) {
            growCluster(ix - 1, iy+1, clusid);
        }
    }

private:
	Calorimeter* obj;
    int _i=0 , _j=0;
    int clusterid=0;


};

#endif
