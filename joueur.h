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
    joueur();
    int getIndexQuadActif() const;
    void setIndexQuadActif(int newIndexQuadActif);

    terrain getTerrainActif() const;
    void setTerrainActif(const terrain &newTerrainActif);

    void addQuad1(quadrimon q);
    void addQuad2(quadrimon q);

private:
    quadrimon q1;
    quadrimon q2;

    int indexQuadActif; // 1 ou 2
    terrain terrainActif;
};

#endif // JOUEUR_H
