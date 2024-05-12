#include "joueur.h"

joueur::joueur(){

}

bool joueur::getIndexQuadActif1()
{
    return indexQuadActif1;
}

std::string joueur::getNameQuadActif(){
    if (indexQuadActif1){
        return q1->getName();
    }
    else{
        return q2->getName();
    }
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

bool joueur::est_attaque(int degats, int type) // Renvoie true si plus de quadrimon vivant, false sinon
{
    int k =1;
    if (attaque_boostee(type))k=2;

    if (indexQuadActif1) {
        q1->setPv(q1->getPv()-k*degats);
        if (q1->getPv()<=0) {
            q1_ko=true;
            if (q2_ko) return true;
            switchIndexQuadActif1();
        }
    } else {
        q2->setPv(q2->getPv()-k*degats);
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

int joueur::get_type_attaque(){
    if (indexQuadActif1){
        return q1->getType();
    }
    return q2->getType();
}
std::string joueur::get_q1_txt()
{
    //return std::__cxx11::to_string(reinterpret_cast<std::uintptr_t>(q1));
    return q1->toString();
}

std::string joueur::get_q2_txt()
{
    //return std::__cxx11::to_string(reinterpret_cast<std::uintptr_t>(q2));
    return q2->toString();
}

bool joueur::getQ1_ko() const
{
    return q1_ko;
}

bool joueur::getQ2_ko() const
{
    return q2_ko;
}

bool joueur::attaque_boostee(int type_attaque) //RENVOIE TRUE SI LE TYPE DE L'ATTAQUANT A UN AVANTAGE SUR LE TYPE DU QUAD ACTIF
{
    if(type_attaque==3){ //CAS SPECIAL CAR NE REPOND PAS A LA REGLE DU +1 : type1 > type2 > type3 > type1
        if(indexQuadActif1){
            if(q1->getType()==1){
                return true;
            }
        }else{
            if(q2->getType()==1){
                return true;
            }
        }
    } else {
        if(indexQuadActif1){
            return (q1->getType()-type_attaque == 1);
        } else {
            return (q2->getType()-type_attaque == 1);
        }
    }
    return false;
}
