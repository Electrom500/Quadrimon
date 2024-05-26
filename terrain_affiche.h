#ifndef TERRAIN_AFFICHE_H
#define TERRAIN_AFFICHE_H

#include <qopengl.h>
#include <QColor>
#include <GL/glu.h>
#include <QString>
#include <QImage>

class terrain_affiche
{
private:
    std::string m_type;
    int m_joueur;
    GLUquadric* m_Quadric;
    GLuint texture[2];
    QImage sol;
    QImage fond;
public:
    terrain_affiche(std::string type, int joueur);
    virtual ~terrain_affiche();
    void Display();
    void changeTerr(std::string type);

};

#endif // TERRAIN_AFFICHE_H
