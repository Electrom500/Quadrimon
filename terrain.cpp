#include "terrain.h"
#include <vector>
#include <algorithm>

std::vector<std::string> allQuadrimon = {"chat", "foret", "grotte", "infirmerie","marais","ouragan","plage","toile","volcan","None"};

int trouverIndice(const std::vector<std::string>& liste, const std::string& recherche) {
    auto it = std::find(liste.begin(), liste.end(), recherche);
    if (it != liste.end()) {
        return std::distance(liste.begin(), it);
    } else {
        return -1;
    }
}

terrain::terrain(){}

terrain::terrain(std::string _name)
{
    name = _name;
    int id = trouverIndice(allQuadrimon,name)+1;
    switch (id) {
    case 10: // None
        terrain_valid = false;
        break;

    case 1: // chat
        nb_tours=2;
        effet_spe=false;
        break;

    case 2: // foret
        nb_tours=-1;
        effet_spe=false;
        break;

    case 3: // grotte
        nb_tours=2;
        effet_spe=false;
        break;

    case 4: // infirmerie
        nb_tours=3;
        effet_spe=true;
        value = -1000;
        break;

    case 5: // marais
        nb_tours=5;
        effet_spe=true;
        value = 50;
        break;

    case 6: // ouragan
        nb_tours=3;
        effet_spe=true;
        value = 100;
        break;

    case 7: // plage
        nb_tours=-1;
        effet_spe=false;
        break;

    case 8: // toile
        nb_tours=3;
        effet_spe=false;
        break;

    case 9: // volcan
        nb_tours=-1;
        effet_spe=false;
        break;

    default:
        terrain_valid = false;
        std::cout << "ERROR OPTION IMPOSSIBLE" << std::endl;
        break;
    }

}

std::string terrain::getName() const
{
    return name;
}

void terrain::setName(const std::string &newName)
{
    name = newName;
}

int terrain::getNb_tours() const
{
    return nb_tours;
}

void terrain::setNb_tours(int newNb_tours)
{
    nb_tours = newNb_tours;
}

int terrain::getEffet_spe() const
{
    return effet_spe;
}

void terrain::setEffet_spe(int newEffet_spe)
{
    effet_spe = newEffet_spe;
}

bool terrain::reduc_tour()
{
    if (nb_tours!=-1){
        nb_tours -=1;
    } else if (nb_tours==1){
        nb_tours =0;
        return false;
    }
    return true;
}

bool terrain::getTerrain_valid() const
{
    return terrain_valid;
}

int terrain::getValue() const
{
    return value;
}
