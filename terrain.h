#ifndef TERRAIN_H
#define TERRAIN_H
#include "iostream"
using namespace std;

class terrain
{
public:
    terrain();
    terrain(string _name,int _nb_tours,bool _permanant);

    string getName() const;
    void setName(const string &newName);

    int getNb_tours() const;
    void setNb_tours(int newNb_tours);

    bool getPermanant() const;
    void setPermanant(bool newPermanant);

private:
    string name;
    int nb_tours;
    bool permanant;
};

#endif // TERRAIN_H
