#ifndef TERRAIN_H
#define TERRAIN_H
#include "iostream"


class terrain
{
public:
    terrain();
    terrain(std::string _name);

    std::string getName();
    void setName(const std::string &newName);

    int getNb_tours();
    void setNb_tours(int newNb_tours);

    int getEffet_spe();
    void setEffet_spe(int newEffet_spe);

    void reduc_tour();
    bool getTerrain_valid();

    int getValue();

    bool getTerrain_enable();

private:
    bool terrain_valid = true;
    bool terrain_enable = true;
    std::string name;
    int nb_tours; // PERMANANT SI =-1
    bool effet_spe; // true = modification des pv par value || false si effet chiant
    int value = 0;

};

#endif // TERRAIN_H
