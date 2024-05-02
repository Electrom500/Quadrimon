#include "joueur.h"

joueur::joueur(){

}

int joueur::getIndexQuadActif() const
{
    return indexQuadActif;
}

void joueur::setIndexQuadActif(int newIndexQuadActif)
{
    indexQuadActif = newIndexQuadActif;
}

terrain joueur::getTerrainActif() const
{
    return terrainActif;
}

void joueur::setTerrainActif(const terrain &newTerrainActif)
{
    terrainActif = newTerrainActif;
}

void joueur::addQuad1(quadrimon q)
{
    q1=q;
}

void joueur::addQuad2(quadrimon q)
{
    q2=q;
}
