#include "joueur.h"

joueur::joueur(){

}

bool joueur::getIndexQuadActif1()
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
    q1=q;
}

void joueur::addQuad2(quadrimon* q)
{
    q2=q;
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

string joueur::get_q1_txt()
{
    //return std::to_string(reinterpret_cast<std::uintptr_t>(q1));
    return q1->toString();
}

string joueur::get_q2_txt()
{
    //return std::to_string(reinterpret_cast<std::uintptr_t>(q2));
    return q2->toString();
}
