#include "reco_carte.h"
#include "ui_reco_carte.h"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int Reco_carte::Capture()
{
    VideoCapture cap(0); // open the default camera
    cap.set(CAP_PROP_FRAME_WIDTH,10000);
    cap.set(CAP_PROP_FRAME_HEIGHT,10000);

    cap.set(CAP_PROP_FRAME_WIDTH,640);
    cap.set(CAP_PROP_FRAME_HEIGHT,480);

    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
        return 0;
    }

    Mat frame;
    cap >> frame; // get a new frame from camera
    captureMat = frame;

    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

Reco_carte::Reco_carte(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reco_carte)
{

    Capture();
    QImage img(captureMat.data, captureMat.cols,captureMat.rows, captureMat.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img);
    ui->capture_label->setPixmap(pixmap);
    ui->setupUi(this);
}

Reco_carte::~Reco_carte()
{
    delete ui;
}




