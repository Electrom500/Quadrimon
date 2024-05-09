#include "joueur.h"

joueur::joueur(){

}

bool joueur::getIndexQuadActif1() const
{
    return indexQuadActif1;
}

void joueur::switchIndexQuadActif1()
{
    indexQuadActif1 = !indexQuadActif1 ;
}

terrain joueur::getTerrainActif() const
{
    return terrainActif;
}

void joueur::setTerrainActif(const terrain &newTerrainActif)
{
    terrainActif = newTerrainActif;
}

void joueur::addQuad1(quadrimon* q)
{
    if (!q1add){
        q1=q;
        q1add=true;
    } else {
        cout<<q1->toString()<<endl;
    }
}

void joueur::addQuad2(quadrimon* q)
{
    if (!q2add){
        q2=q;
        q2add=true;
    }else {
        cout<<q2->toString()<<endl;
    }
}

bool joueur::est_attaque(int degats) // Renvoie true si plus de quadrimon vivant, false sinon
{
    if (indexQuadActif1) {
        q1->setPv(q1->getPv()-degats);
        if (q1->getPv()<=0) {
            q1_ko=true;
            if (q2_ko) return true;
            switchIndexQuadActif1();
        }
    } else {
        q2->setPv(q2->getPv()-degats);
        if (q2->getPv()<=0){
            q2_ko=true;
            if (q1_ko) return true;
        }
    }
    return false;
}

int joueur::degats_a_infliger()
{
    if (indexQuadActif1) return q1->getAttaque();
    return q2->getAttaque();
}
