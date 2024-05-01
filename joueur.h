#ifndef JOUEUR_H
#define JOUEUR_H

#include <array>
#include <iostream>
#include "terrain.h"
#include "quadrimon.h"
using namespace std;
class joueur
{
public:
    joueur(quadrimon q1,quadrimon q2,int _indexQuadActif,terrain _terrainActif);
    int getIndexQuadActif() const;
    void setIndexQuadActif(int newIndexQuadActif);

    terrain getTerrainActif() const;
    void setTerrainActif(const terrain &newTerrainActif);

private:
    array<quadrimon,2> lst_quadrimons;
    int indexQuadActif;
    terrain terrainActif;
};

#endif // JOUEUR_H
