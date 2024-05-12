#ifndef TERRAIN_H
#define TERRAIN_H
#include "iostream"


class terrain
{
public:
    terrain();
    terrain(std::string _name,int _nb_tours,bool _permanant);

    std::string getName() const;
    void setName(const std::string &newName);

    int getNb_tours() const;
    void setNb_tours(int newNb_tours);

    bool getPermanant() const;
    void setPermanant(bool newPermanant);

private:
    std::string name;
    int nb_tours;
    bool permanant;
};

#endif // TERRAIN_H
