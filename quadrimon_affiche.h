#ifndef QUADRIMON_AFFICHE_H
#define QUADRIMON_AFFICHE_H


#include <qopengl.h>
#include <QColor>
#include <GL/glu.h>
#include <QString>



class quadrimon_affiche
{
private :
    std::string m_quad;
    int m_joueur;
    bool m_att;
    float t_att;
    float m_time;
    GLUquadric* m_Quadric;

public:
    quadrimon_affiche(std::string quad, int joueur);
    virtual ~quadrimon_affiche();
    void Display(const float time);
    void attaque();

    void setTime(float time){m_time=time;}
};

#endif // QUADRIMON_AFFICHE_H
