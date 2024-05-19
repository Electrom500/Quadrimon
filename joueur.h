#ifndef JOUEUR_H
#define JOUEUR_H


#include <stack>

#include "terrain.h"
#include "quadrimon.h"
class joueur
{
public:
    joueur();
    bool getIndexQuadActif1();
    void switchIndexQuadActif1();

    terrain* getTerrainActif();
    void setTerrainActif(terrain* newTerrainActif);

    void addQuad1(quadrimon* q1);
    void addQuad2(quadrimon* q2);

    bool est_attaque(int degats,int type);
    int degats_a_infliger();

    std::string get_q1_txt();
    std::string get_q2_txt();

    bool getQ1_ko() const;
    bool getQ2_ko() const;

    std::string getNameQuadActif();

    int get_type_attaque();
private:
    bool ko = false;
    bool q1_ko =false;
    bool q2_ko =false;

    quadrimon* q1 = new quadrimon;
    quadrimon* q2 = new quadrimon;

    bool attaque_boostee(int type_attaque);

    bool indexQuadActif1 = true; // true = 1, false = 2
    terrain* terrainActif;
};

#endif // JOUEUR_H
