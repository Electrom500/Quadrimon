#include "quadrimon.h"
#include <vector>
#include <algorithm>
using namespace std;
vector<string> allQuadrimon = {"Cylindrus", "Gizeh", "Flamby", "Khone","Menu","Olaf","Saladier","Soleil","Glace","None"};

int trouverIndice(const vector<string>& liste, const string& recherche) {
    auto it = find(liste.begin(), liste.end(), recherche);
    if (it != liste.end()) {
        return distance(liste.begin(), it);
    } else {
        return -1;
    }
}

quadrimon::quadrimon()
{
}

quadrimon::quadrimon(string _name)
{
    name = _name;
    int id = trouverIndice(allQuadrimon,name)+1;
    switch (id) {
    case 10:
        break;

    case 1: // Cylindrus
        setQuad_valid(true);
        type = 3;
        attaque = 50;
        pv = 700;
        break;

    case 2: // Gizeh
        setQuad_valid(true);
        type = 1;
        attaque = 400;
        pv = 200;
        break;

    case 3: // Flamby
        setQuad_valid(true);
        type = 2;
        attaque = 0;
        pv = 900;
        break;

    case 4: // Khone
        setQuad_valid(true);
        type = 1;
        attaque = 350;
        pv = 350;
        break;

    case 5: // Menu
        setQuad_valid(true);
        type = 2;
        attaque = 200;
        pv = 500;
        break;

    case 6: // Olaf
        setQuad_valid(true);
        type = 3;
        attaque = 150;
        pv = 500;
        break;

    case 7: // Saladier
        setQuad_valid(true);
        type = 2;
        attaque = 100;
        pv = 800;
        break;

    case 8: // Soleil
        setQuad_valid(true);
        type = 1;
        attaque = 150;
        pv = 400;
        break;

    case 9: // Glace
        setQuad_valid(true);
        type = 3;
        attaque = 100;
        pv = 600;
        break;

    default:

        cout << "ERROR OPTION IMPOSSIBLE" << endl;
        break;
    }
}

string quadrimon::getName() const
{
    return name;
}

void quadrimon::setName(const string &newName)
{
    name = newName;
}

int quadrimon::getType() const
{
    return type;
}

void quadrimon::setType(int newType)
{
    type = newType;
}

int quadrimon::getPv() const
{
    return pv;
}

void quadrimon::setPv(int newPv)
{
    pv = newPv;
}

bool quadrimon::getQuad_valid() const
{
    return quad_valid;
}

void quadrimon::setQuad_valid(bool newQuad_valid)
{
    quad_valid = newQuad_valid;
}

string quadrimon::toString()
{
    string strType = "";
    if (type==1){
        strType = "Eau";
    } else if (type==2){
        strType = "Feu";
    } else if (type==3){
        strType = "Vent";
    }
    string str = " Nom = " + name +
                 "\n Type = " + strType +
                 "\n PV = " + to_string(pv) +
                 "\n Attaque = " + to_string(attaque);
    return str;
}

int quadrimon::getAttaque() const
{
    return attaque;
}

void quadrimon::setAttaque(int newAttaque)
{
    attaque = newAttaque;
}
