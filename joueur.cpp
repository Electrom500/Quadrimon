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
    if (!q1add){
        q1=q;
        q1add=true;
    } else {
        cout<<q1.toString()<<endl;
    }
}

void joueur::addQuad2(quadrimon q)
{
    if (!q2add){
        q2=q;
        q2add=true;
    }else {
        cout<<q2.toString()<<endl;
    }
}
