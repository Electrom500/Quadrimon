#include "reco_carte.h"
#include "ui_reco_carte.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include "QTimer"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"

using namespace cv;
using namespace std;

const char* keys =
    "{ help h |                  | Print help message. }"
    "{ input1 | box.png          | Path to input image 1. }"
    "{ input2 | box_in_scene.png | Path to input image 2. }";

void Reco_carte::detectCard(int argc, char *argv[])
{
    CommandLineParser parser( argc, argv, keys );
    Mat img1 = imread("C:/Users/damie/Desktop/Cours/Telecom/FISE 2/Bibliotheques de dev multimedia/test_flann_matching/cylindrus.png", IMREAD_GRAYSCALE);
    Mat img2 = imread( samples::findFile( parser.get<String>("input2") ), IMREAD_GRAYSCALE );
    if ( img1.empty() || img2.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        parser.printMessage();
    }

    //-- Step 1: Detect the keypoints using SIFT Detector, compute the descriptors
    Ptr<SIFT> detector = SIFT::create( );
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    detector->detectAndCompute( img1, noArray(), keypoints1, descriptors1 );
    detector->detectAndCompute( img2, noArray(), keypoints2, descriptors2 );

    //-- Step 2: Matching descriptor vectors with a FLANN based matcher
    // Since SIFT is a floating-point descriptor NORM_L2 is used
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<DMatch> > knn_matches;
    matcher->knnMatch( descriptors1, descriptors2, knn_matches, 2 );

    //-- Filter matches using the Lowe's ratio test
    const float ratio_thresh = 0.7f;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }
    cout<<"Il y a : "<< good_matches.size()<< "good matches "<<endl;
}


void Reco_carte::Capture()
{
    if(!capture.isOpened())
    {
        cerr<<"Error opening the default camera"<<endl;
    }

    Mat frame;

        capture >> frame; // get a new frame from camera

        // Check if the frame is empty
        if (frame.empty()) {
            cerr << "Error: Captured frame is empty" << endl;

        }

        captureMat = frame;
        //imshow("test",frame);

}

void Reco_carte::updateImage()
{
    Capture();
    QSize labelSize = ui->capture_label->size();

    Mat resizedFrame;
    cv::resize(captureMat, resizedFrame, cv::Size(labelSize.width(), labelSize.height()));

    QImage img(resizedFrame.data, resizedFrame.cols, resizedFrame.rows, resizedFrame.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img);

    ui->capture_label->setPixmap(pixmap);
}

Reco_carte::Reco_carte(int argc, char *argv[],QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reco_carte)
{
    ui->setupUi(this);
    capture = VideoCapture(0);
    detectCard(argc,argv);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateImage()));
    timer->start(20); // Interval in milliseconds
}

Reco_carte::~Reco_carte()
{
    delete ui;
}




