#ifndef SCENE_H
#define SCENE_H

#include "quadrimon_affiche.h"
#include "terrain_affiche.h"
#include <QTimer>
#include <QtOpenGLWidgets/QOpenGLWidget>

class scene : public QOpenGLWidget
{
    Q_OBJECT

public:
    scene(QWidget * parent = nullptr);
    virtual ~scene();


    void changeQuadJ1(std::string nom);
    void changeTerrJ1(std::string nom);
    void changeQuadJ2(std::string nom);
    void changeTerrJ2(std::string nom);

    void attaqueQuadJ1();
    void attaqueQuadJ2();

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();


private:
    quadrimon_affiche* quadD;
    quadrimon_affiche* quadG;
    terrain_affiche* terrD;
    terrain_affiche* terrG;

    // Timer d'animation
    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
};

#endif // SCENE_H
