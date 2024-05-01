#include "quadrimon.h"


quadrimon::quadrimon(string _name, int _type, int _attaque, int _pv)
{
    name = _name;
    type = _type;
    attaque = _attaque;
    pv = _pv;
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

int quadrimon::getAttaque() const
{
    return attaque;
}

void quadrimon::setAttaque(int newAttaque)
{
    attaque = newAttaque;
}
