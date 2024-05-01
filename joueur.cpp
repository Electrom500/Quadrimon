#include "joueur.h"

joueur::joueur(quadrimon q1, quadrimon q2, int _indexQuadActif, terrain _terrainActif) : lst_quadrimons({q1, q2}), indexQuadActif(_indexQuadActif), terrainActif(_terrainActif) {}

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

