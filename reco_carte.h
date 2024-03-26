#ifndef RECO_CARTE_H
#define RECO_CARTE_H

#include <QDialog>
#include <iostream>
#include "opencv2/opencv.hpp"
namespace Ui {
class Reco_carte;
}

class Reco_carte : public QDialog
{
    Q_OBJECT

public:
    explicit Reco_carte(int argc, char *argv[],QWidget *parent = 0);
    ~Reco_carte();
    cv::Mat captureMat;
    void Capture();
    void Start();
    cv::VideoCapture capture;
    void detectCard(int argc, char *argv[]);
private:



private slots:
    void updateImage();
private:
    Ui::Reco_carte *ui;
};

#endif // RECO_CARTE_H
