#include "terrain.h"


terrain::terrain(){}

terrain::terrain(std::string _name, int _nb_tours, bool _permanant)
{
    name = _name;
    nb_tours = _nb_tours;
    permanant = _permanant;
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

bool terrain::getPermanant() const
{
    return permanant;
}

void terrain::setPermanant(bool newPermanant)
{
    permanant = newPermanant;
}
