#ifndef RECO_TERRAIN_H
#define RECO_TERRAIN_H

#include <QDialog>
#include <iostream>
#include "opencv2/opencv.hpp"

#include "mainwindow.h"


namespace Ui {
class Reco_terrain;
}

class Reco_terrain : public QDialog
{
    Q_OBJECT

public:
    explicit Reco_terrain(MainWindow *mw,QWidget *parent = 0);
    ~Reco_terrain();
    cv::Mat captureMat;
    void Capture();
    void Start();
    cv::VideoCapture capture;
    int detectCard(std::string path);

    std::string getLast_carte_detect() const;
    void setLast_carte_detect(const std::string &newLast_carte_detect);

    Ui::Reco_terrain *ui;

private:

    MainWindow *mw;
    void actualiser_card_match_label(std::string path);
    void charger_image(QString cheminImage);
    std::string last_carte_detect = "None";


private slots:
    void updateImage();
    void testCartes();
    void on_capture_button_clicked();

    void on_valid_button_clicked();

};

#endif // RECO_TERRAIN_H
