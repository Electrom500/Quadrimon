#ifndef TERRAIN_H
#define TERRAIN_H
#include "iostream"


class terrain
{
public:
    terrain();
    terrain(std::string _name);

    std::string getName() const;
    void setName(const std::string &newName);

    int getNb_tours() const;
    void setNb_tours(int newNb_tours);

    int getEffet_spe() const;
    void setEffet_spe(int newEffet_spe);

    bool reduc_tour();
    bool getTerrain_valid() const;

    int getValue() const;

private:
    bool terrain_valid = true;
    std::string name;
    int nb_tours; // PERMANANT SI =-1
    bool effet_spe; // true = modification des pv par value || false si effet chiant
    int value = 0;

};

#endif // TERRAIN_H
