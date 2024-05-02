#ifndef QUADRIMON_H
#define QUADRIMON_H
#include "iostream"
using namespace std;
class quadrimon
{
public:
    quadrimon();
    quadrimon(string _name);
    string getName() const;
    void setName(const string &newName);

    int getType() const;
    void setType(int newType);

    int getAttaque() const;
    void setAttaque(int newAttaque);

    int getPv() const;
    void setPv(int newPv);

    bool getQuad_valid() const;
    void setQuad_valid(bool newQuad_valid);
    string toString();
private:
    string name;
    int type =0; // 1 = feu , 2 = vent , 3 = eau
    int attaque=0;
    int pv=0;
    bool quad_valid = false;
};

#endif // QUADRIMON_H
