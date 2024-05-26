#include "terrain_affiche.h"
#include <QColor>
#include <GL/glu.h>
#include <qopengl.h>
#include <iostream>
#include <QImage>
#include <QDebug>


terrain_affiche::terrain_affiche(std::string type, int joueur) {
    m_type=type;
    m_joueur=joueur;
    this->changeTerr("base");

}

terrain_affiche::~terrain_affiche(){
}

void terrain_affiche::Display(){
    glPushMatrix();
    if (m_joueur==1){
        glTranslated(30.0f,0,0);
    }
    else{
        glTranslated(-30.0f,0,0);
    }

    GLfloat colorAmbianteTabfin[] = {0.0,0.0,0.0,1.0};
    GLfloat colorDiffuseTabfin[] = {0.0,0.0,0.0,1.0};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTabfin);
    glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTabfin);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glTranslated(0,10.0f,0);

    int ud = 30;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);glVertex3i(-ud, -ud, -ud);
    glTexCoord2f(0,0);glVertex3i(-ud, +ud, -ud);
    glTexCoord2f(1,0);glVertex3i(+ud, +ud, -ud);
    glTexCoord2f(1,1);glVertex3i(+ud, -ud, -ud);
    glEnd();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);glVertex3i(-ud, -ud, -ud);
    glTexCoord2f(1,0);glVertex3i(+ud, -ud, -ud);
    glTexCoord2f(1,1);glVertex3i(+ud, -ud, +ud);
    glTexCoord2f(0,1);glVertex3i(-ud, -ud, +ud);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}


void terrain_affiche::changeTerr(std::string type){
    m_type = type;
    std::string cheminfond=":/res/fond_"+type+".png";
    std::string cheminsol=":/res/sol_"+type+".png";

    QImage sol(QString::fromStdString(cheminsol));
    sol = sol.convertToFormat(QImage::Format_RGBA8888);

    QImage fond(QString::fromStdString(cheminfond));
    fond = fond.convertToFormat(QImage::Format_RGBA8888);

    //GLuint texture;
    glGenTextures(1,&texture[0]);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glTexImage2D(GL_TEXTURE_2D,0,4,fond.width(),fond.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,fond.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glGenTextures(1,&texture[1]);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    glTexImage2D(GL_TEXTURE_2D,0,4,sol.width(),sol.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,sol.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

