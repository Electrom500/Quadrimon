#include "quadrimon_affiche.h"
#include <GL/glu.h>
#include <qopengl.h>
#include <iostream>

quadrimon_affiche::quadrimon_affiche(std::string quad, int joueur) {

    m_quad=quad;
    m_joueur=joueur;
    m_att = false;

    // Creation de la quadrique
    m_Quadric = gluNewQuadric();
    t_att = -1;
    m_time=0;

}

void quadrimon_affiche::attaque(){
    m_att= true;
    t_att = m_time;
}


quadrimon_affiche::~quadrimon_affiche(){
    // Destruction de la quadrique
    gluDeleteQuadric(m_Quadric);
}


void quadrimon_affiche::Display(const float time)
{
    setTime(time);
    glEnable(GL_LIGHTING);
    glPushMatrix();
    if (m_joueur==1){
        glTranslated(-30.0f,0,0);
    }
    else{
        glTranslated(30.0f,0,0);
    }

    if(t_att!=-1){
        if(m_time - t_att > 1){
            m_att = false;
            t_att = -1;
        }
    }


    if (!m_att){
        glTranslated(0,2*sin(time),0);
    }
    else{
        glTranslated(0,-10,0);
        if(m_joueur==1){
            glRotated(30+sin(4*(time-t_att))*30,0,0,1);
        }
        else{
            glRotated(-30-sin(4*(time-t_att))*30,0,0,1);
        }
        glTranslated(0,10,0);
    }



    if (m_quad=="Soleil"){
        // Couleur de l'objet
        GLfloat colorAmbianteTab1[] = {1.0,0.0,0.0,0.0};
        GLfloat colorDiffuseTab1[] = {1.0,1.0,1.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        // Affichage de la quadrique
        gluSphere(m_Quadric,10,20,20);
    }

    else if(m_quad=="Khone"){
        // Couleur de l'objet
        //glColor3f(1.0f,0.0f,0.0f);
        glTranslated(0.0,-13.0,0.0);
        glRotated(-90.,1.,0.,0.);
        GLfloat colorAmbianteTab1[] = {1.0,0.0,0.0,0.0};
        GLfloat colorDiffuseTab1[] = {1.0,1.0,1.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        // Affichage de la quadrique
        gluCylinder(m_Quadric,0,10,20,20,1);
    }

    else if(m_quad=="Gizeh"){
        // Couleur de l'objet
        //glColor3f(1.0f,0.0f,0.0f);
        glRotated(90.,1.,0.,0.);
        glTranslated(0.0,-40.0,0.0);
        GLfloat colorAmbianteTab1[] = {1.0,1.0,0.0,0.0};
        GLfloat colorDiffuseTab1[] = {1.0,1.0,1.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        // Affichage de la quadrique
        gluCylinder(m_Quadric,0,10,20,4,1);
    }

    else if(m_quad=="Menu"){
        // Couleur de l'objet
        glRotated(50.,1.,0.,0.);

        glColor3f(0.0,1.0,0.0);
        //glTranslated(0.0,-40.0,0.0);
        GLfloat colorAmbianteTab1[] = {.0,.0,.0,0.0};
        GLfloat colorDiffuseTab1[] = {0.0,0.7,0.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        int numc = 100, numt = 100;

        double TWOPI = 2 * 3.14159281;
        for (int i = 0; i < numc; i++) {
            glBegin(GL_QUAD_STRIP);
            for (int j = 0; j <= numt; j++) {
                for (int k = 1; k >= 0; k--) {

                    double s = (i + k) % numc + 5.0;
                    double t = j % numt;

                    double x = (6 + 1.5 * cos(s * TWOPI / numc)) * cos(t * TWOPI / numt);
                    double y = (6 + 1.5 * cos(s * TWOPI / numc)) * sin(t * TWOPI / numt);
                    double z = 1.5 * sin(s * TWOPI / numc);

                    glVertex3d(2 * x, 2 * y, 2 * z);
                }
            }
            glEnd();
        }
    }

    else if(m_quad=="Flamby"){
        // Couleur de l'objet
        //glColor3f(1.0f,0.0f,0.0f);
        glTranslated(0.0,-5.0,0.0);
        glRotated(35.,0.,1.,0.);
        glRotated(5.,1.,0.,0.);
        GLfloat colorAmbianteTab1[] = {0.0,1.0,0.0,0.0};
        GLfloat colorDiffuseTab1[] = {1.0,1.0,1.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        glBegin(GL_QUADS);

        // Face avant
        glVertex3f(0.f, 15.f, 15.f);
        glVertex3f(15.f, 15.f, 15.f);
        glVertex3f(15.f, 0.f, 15.f);
        glVertex3f(0.f, 0.f, 15.f);

        // Face arrière
        glVertex3f(0.f, 15.f, 0.f);
        glVertex3f(15.f, 15.f, 0.f);
        glVertex3f(15.f, 0.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);

        // Face gauche
        glVertex3f(0.f, 15.f, 15.f);
        glVertex3f(0.f, 15.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(0.f, 0.f, 15.f);

        // Face droite
        glVertex3f(15.f, 15.f, 15.f);
        glVertex3f(15.f, 15.f, 0.f);
        glVertex3f(15.f, 0.f, 0.f);
        glVertex3f(15.f, 0.f, 15.f);

        // Face supérieure
        glVertex3f(0.f, 15.f, 15.f);
        glVertex3f(15.f, 15.f, 15.f);
        glVertex3f(15.f, 15.f, 0.f);
        glVertex3f(0.f, 15.f, 0.f);

        // Face inférieure
        glVertex3f(0.f, 0.f, 15.f);
        glVertex3f(15.f, 0.f, 15.f);
        glVertex3f(15.f, 0.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);

        glEnd();
    }

    else if(m_quad == "Saladier"){
        GLfloat radius = 10.0f;
        GLint slices=32;
        GLint stacks=32;

        glRotated(180.,1.,0.,0.);
        GLfloat colorAmbianteTab1[] = {0.0,1.0,0.0,0.0};
        GLfloat colorDiffuseTab1[] = {1.0,1.0,1.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        for (int i = 0; i < slices; ++i) {
            glBegin(GL_QUAD_STRIP);
            for (int j = 0; j <= stacks / 2; ++j) {
                double theta1 = i * M_PI / slices;
                double theta2 = (i + 1) * M_PI / slices;
                double phi = j * M_PI / stacks;
                double nextPhi = (j + 1) * M_PI / stacks;

                double x1 = radius * sin(phi) * cos(theta1);
                double y1 = radius * sin(phi) * sin(theta1);
                double z1 = radius * cos(phi);

                double x2 = radius * sin(phi) * cos(theta2);
                double y2 = radius * sin(phi) * sin(theta2);
                double z2 = radius * cos(phi);

                double x3 = radius * sin(nextPhi) * cos(theta1);
                double y3 = radius * sin(nextPhi) * sin(theta1);
                double z3 = radius * cos(nextPhi);

                double x4 = radius * sin(nextPhi) * cos(theta2);
                double y4 = radius * sin(nextPhi) * sin(theta2);
                double z4 = radius * cos(nextPhi);

                glVertex3d(x1, y1, z1);
                glVertex3d(x2, y2, z2);
                glVertex3d(x3, y3, z3);
                glVertex3d(x4, y4, z4);
            }
            glEnd();
        }

        GLfloat colorAmbianteTab2[] = {0.0,0.0,0.0,1.0};
        GLfloat colorDiffuseTab2[] = {0.0,0.0,0.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab2);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab2);
    }

    else if(m_quad == "Cylindrus"){
        glRotated(90,1.0,0.0,0.0);
        glTranslated(0,-30,0);
        GLfloat colorAmbianteTab1[] = {0.0,0.0,1.0,0.0};
        GLfloat colorDiffuseTab1[] = {1.0,1.0,1.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        // Affichage de la quadrique
        gluCylinder(m_Quadric,3,3,20,50,1);

    }

    else if(m_quad == "Glace"){
        glRotated(90,1.0,0.0,0.0);
        GLfloat colorAmbianteTab1[] = {0.0,0.0,1.0,0.0};
        GLfloat colorDiffuseTab1[] = {1.0,1.0,1.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        // Affichage de la quadrique
        gluCylinder(m_Quadric,5,0,15,50,1);
        gluSphere(m_Quadric,5,50,50);
    }

    else if(m_quad == "Olaf"){
        glTranslated(0,10,0);
        GLfloat colorAmbianteTab1[] = {0.0,0.0,1.0,0.0};
        GLfloat colorDiffuseTab1[] = {1.0,1.0,1.0,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTab1);
        glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTab1);

        // Affichage de la quadrique
        gluSphere(m_Quadric,3,50,50);
        glTranslated(0.0,-7.0,0.0);
        gluSphere(m_Quadric,5,50,50);
        glTranslated(0.0,-10.0,0.0);
        gluSphere(m_Quadric,7,50,50);
    }

    glPopMatrix();

    GLfloat colorAmbianteTabfin[] = {0.0,0.0,0.0,1.0};
    GLfloat colorDiffuseTabfin[] = {0.0,0.0,0.0,1.0};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuseTabfin);
    glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbianteTabfin);
    glDisable(GL_LIGHTING);


}


