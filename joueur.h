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
    bool getIndexQuadActif1();
    void switchIndexQuadActif1();

    terrain getTerrainActif() const;
    void setTerrainActif(const terrain &newTerrainActif);

    void addQuad1(quadrimon* q1);
    void addQuad2(quadrimon* q2);

    bool est_attaque(int degats);
    int degats_a_infliger();

    string get_q1_txt();
    string get_q2_txt();

    bool getQ1_ko() const;
    bool getQ2_ko() const;

private:
    bool ko = false;
    bool q1_ko =false;
    bool q2_ko =false;

    quadrimon* q1 = new quadrimon;
    quadrimon* q2 = new quadrimon;

    bool indexQuadActif1 = true; // true = 1, false = 2
    terrain terrainActif;
};

#endif // JOUEUR_H
