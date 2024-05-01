#ifndef RECO_CARTE_H
#define RECO_CARTE_H

#include <QDialog>
#include <iostream>
#include "opencv2/opencv.hpp"

#include "mainwindow.h"

using namespace std;
namespace Ui {
class Reco_carte;
}

class Reco_carte : public QDialog
{
    Q_OBJECT

public:
    explicit Reco_carte(MainWindow *mw,QWidget *parent = 0);
    ~Reco_carte();
    cv::Mat captureMat;
    void Capture();
    void Start();
    cv::VideoCapture capture;
    int detectCard(string path);

private:
    MainWindow *mw;
    void actualiser_card_match_label(string path);
    void charger_image(QString cheminImage);


private slots:
    void updateImage();
    void testCartes();
    void on_capture_button_clicked();

private:
    Ui::Reco_carte *ui;
};

#endif // RECO_CARTE_H
