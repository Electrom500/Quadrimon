#ifndef QUADRIMON_H
#define QUADRIMON_H
#include "iostream"
using namespace std;
class quadrimon
{
public:
    quadrimon(string _name,int _type,int _attaque,int _pv);
    string getName() const;
    void setName(const string &newName);

    int getType() const;
    void setType(int newType);

    int getAttaque() const;
    void setAttaque(int newAttaque);

    int getPv() const;
    void setPv(int newPv);

private:
    string name;
    int type; // 1 = feu , 2 = vent , 3 = eau
    int attaque;
    int pv;
};

#endif // QUADRIMON_H
