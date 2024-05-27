#include "scene.h"
#include "quadrimon_affiche.h"
#include <GL/glu.h>
#include <QString>
#include <iostream>
#include <QKeyEvent>

// Declarations des constantes
const unsigned int WIN_WIDTH = 400;
const unsigned int WIN_HEIGHT = 800;
const float MAX_DIMENSION     = 50.0f;

scene::scene(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setFixedSize(WIN_HEIGHT, WIN_WIDTH);
    //resize(WIN_WIDTH_HEIGHT, WIN_WIDTH_HEIGHT);

    // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 0.10f;
        if (m_TimeElapsed>10.1){
            //m_TimeElapsed=0;
        };
        update();
    });


    m_AnimationTimer.setInterval(5);
    m_AnimationTimer.start();
}

scene::~scene(){
    delete quadD;
    delete quadG;
    delete terrD;
    delete terrG;
}

// Fonction d'initialisation
void scene::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(1,1,1,0);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);

    quadD=new quadrimon_affiche("",1);
    quadG=new quadrimon_affiche("",2);

    terrD=new terrain_affiche("",1);
    terrG=new terrain_affiche("",2);

}


// Fonction de redimensionnement
void scene::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

// Fonction d'affichage
void scene::paintGL()
{
    // Reinitialisation des tampons
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //const GLfloat angle = 70;
    //glLightfv(GL_LIGHT0,GL_SPOT_CUTOFF,angle);
    GLfloat a[] = {0.0, 100.0, 50.0, 1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,a);
    // Definition de la position de la camera
    glLoadIdentity();
    gluLookAt(0, 10,40,0,0,-1,0,1,0);

    // Affichage des terrains
    terrG->Display();
    terrD->Display();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Affichage des quadrimons
    quadG->Display(m_TimeElapsed);
    quadD->Display(m_TimeElapsed);

}

void scene::changeQuadJ1(std::string nom){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    quadG->changeQuad(nom);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}

void scene::changeQuadJ2(std::string nom){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    quadD->changeQuad(nom);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}

void scene::changeTerrJ1(std::string nom){
    glDisable(GL_LIGHTING);
    terrG->changeTerr(nom);
    glDisable(GL_LIGHTING);
}

void scene::changeTerrJ2(std::string nom){
    glDisable(GL_LIGHTING);

    terrD->changeTerr(nom);
    glDisable(GL_LIGHTING);
}

quadrimon_affiche* scene::getQuadD(){
    return quadD;
}
quadrimon_affiche* scene::getQuadG(){
    return quadG;
}
