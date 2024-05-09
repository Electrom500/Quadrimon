#ifndef JOUEUR_H
#define JOUEUR_H


#include <stack>

#include "terrain.h"
#include "quadrimon.h"
using namespace std;
class joueur
{
public:
    joueur();
    bool getIndexQuadActif1() const;
    void switchIndexQuadActif1();

    terrain getTerrainActif() const;
    void setTerrainActif(const terrain &newTerrainActif);

    void addQuad1(quadrimon* q);
    void addQuad2(quadrimon* q);

    bool q1add = false; // Sécurités suite a des tests foireux
    bool q2add = false; // Sécurités suite a des tests foireux

    bool est_attaque(int degats);

private:
    bool ko = false;
    bool q1_ko =false;
    bool q2_ko =false;

    quadrimon* q1;
    quadrimon* q2;

    bool indexQuadActif1 = true; // true = 1, false = 2
    terrain terrainActif;
};

#endif // JOUEUR_H
