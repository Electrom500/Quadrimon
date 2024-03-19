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
    explicit Reco_carte(QWidget *parent = nullptr);
    ~Reco_carte();
    cv::Mat captureMat;
    int Capture();

private:
    Ui::Reco_carte *ui;
};

#endif // RECO_CARTE_H
