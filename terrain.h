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

    bool getEffet_unique_done() const;
    void setEffet_unique_done(bool newEffet_unique_done);

private:
    bool terrain_valid = true; //si le terrain est un terrain possible normalement pas utilise
    bool terrain_enable = true; // Identifie si le terrain est actif ou expire
    std::string name;
    int nb_tours; // PERMANANT = -1
    bool effet_spe; // true = modification des pv par value || false si effet chiant
    bool effet_unique_done = false; // pour ceux qui ont un effet qui doit se faireu une seule fois comme toile
    int value = 0;

};

#endif // TERRAIN_H
