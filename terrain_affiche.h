#ifndef TERRAIN_AFFICHE_H
#define TERRAIN_AFFICHE_H

#include <qopengl.h>
#include <QColor>
#include <GL/glu.h>
#include <QString>


class terrain_affiche
{
    std::string m_type;
    int m_joueur;
    GLUquadric* m_Quadric;
public:
    terrain_affiche(std::string type, int joueur);
    virtual ~terrain_affiche();
    void Display() const;
};

#endif // TERRAIN_AFFICHE_H
