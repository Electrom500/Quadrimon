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

int Reco_carte::detectCard(string path)
{
    if (!captureMat.empty()){
    Mat img1 = imread(path, IMREAD_GRAYSCALE);
    Mat img2 = captureMat;
    if ( img1.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
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
    matcher->knnMatch( descriptors1, descriptors2, knn_matches,5);

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
    //cout<<"Il y a : "<< good_matches.size()<< "good matches "<<endl;
    return good_matches.size();
    }
    return 0;

}


void Reco_carte::Capture()

{
    if(!capture.isOpened())
    {
        cerr<<"Error opening the default camera"<<endl;
    }

    Mat frame;

        capture >> frame; //new frame from camera

        // check if the frame is empty
        if (frame.empty()) {
            cerr << "Error: Captured frame is empty" << endl;

        }

        captureMat = frame;
        //imshow("test",frame);
}
void Reco_carte::charger_image(QString cheminImage) {
    // Charge l'image et la redimentionne


    QImage image(cheminImage);
    //QSize tailleTest(100, 100); Test
    QSize tailleLabel = ui->card_match_label->size();

    image = image.scaled(tailleLabel, Qt::KeepAspectRatio); // Garder le ratio d'aspect

    ui->card_match_label->setPixmap(QPixmap::fromImage(image));
}

string Reco_carte::getLast_carte_detect() const
{
    return last_carte_detect;
}

void Reco_carte::setLast_carte_detect(const string &newLast_carte_detect)
{
    last_carte_detect = newLast_carte_detect;
}

void Reco_carte::actualiser_card_match_label(string carte_detect){
    string path ="";
    if (carte_detect == "Cylindrus"){ path = "../quadrimon/cartes/codes/cylindrus.png";}
    else if (carte_detect == "Gizeh"){ path = "../quadrimon/cartes/codes/gizeh.png";}
    else if (carte_detect == "Flamby"){ path = "../quadrimon/cartes/codes/flamby.png";}
    else if (carte_detect == "Khone"){ path = "../quadrimon/cartes/codes/khone.png";}
    else if (carte_detect == "Menu"){ path = "../quadrimon/cartes/codes/menu.png";}
    else if (carte_detect == "Olaf"){ path = "../quadrimon/cartes/codes/olaf.png";}
    else if (carte_detect == "Saladier"){ path = "../quadrimon/cartes/codes/saladier.png";}
    else if (carte_detect == "Soleil"){ path = "../quadrimon/cartes/codes/soleil.png";}
    else if (carte_detect == "Glace"){ path = "../quadrimon/cartes/codes/glace.png";}

    if (path != ""){
        QString Qpath=QString::fromStdString(path);
        charger_image(Qpath);
    } else {
        // TODO ????
    }


}

void Reco_carte::testCartes(){

    int nb_max = 0;
    bool stop = false;

    string path_cyl = "../quadrimon/cartes/codes/cylindrus.png";
    int nb = detectCard(path_cyl)/1.5;
    cout<<nb<<endl;
    string carte_detect = "None";
    if (nb > 20) {
        if(nb>50){stop=true;}
        carte_detect = "Cylindrus";
        nb_max = nb;
    }

    if(!stop){
    string path_gizeh = "../quadrimon/cartes/codes/gizeh.png";
    nb = detectCard(path_gizeh);
    cout<<nb<<endl;
    if (nb > 20 && nb>nb_max){
        if(nb>50){stop=true;}
        carte_detect = "Gizeh";
        nb_max = nb;
    }}

    if(!stop){
    string path_flamby = "../quadrimon/cartes/codes/flamby.png";
    nb = detectCard(path_flamby)*3;
    cout<<nb<<endl;
    if (nb > 20 && nb>nb_max){
        if(nb>50){stop=true;}
        carte_detect = "Flamby";
        nb_max = nb;
    }}

    if(!stop){
    string path_glace = "../quadrimon/cartes/codes/glace.png";
    nb = detectCard(path_glace)/2.3;
    cout<<nb<<endl;
    if (nb > 20 && nb>nb_max){
        if(nb>50){stop=true;}
        carte_detect = "Glace";
        nb_max = nb;
    };}

    if(!stop){
    string path_khone = "../quadrimon/cartes/codes/khone.png";
    nb = detectCard(path_khone)/5;
    cout<<nb<<endl;
    if (nb > 20 && nb>nb_max){
        if(nb>50){stop=true;}
        carte_detect = "Khone";
        nb_max = nb;
    }}

    if(!stop){
    string path_menu = "../quadrimon/cartes/codes/menu.png";
    nb = detectCard(path_menu)/13;
    cout<<nb<<endl;
    if (nb > 20 && nb>nb_max){
        if(nb>50){stop=true;}
        carte_detect = "Menu";
        nb_max = nb;
    }}

    if(!stop){
    string path_olaf = "../quadrimon/cartes/codes/olaf.png";
    nb = detectCard(path_olaf)/3;
    cout<<nb<<endl;
    if (nb > 20 && nb>nb_max){
        if(nb>50){stop=true;}
        carte_detect = "Olaf";
        nb_max = nb;
    }}

    if(!stop){
    string path_sala = "../quadrimon/cartes/codes/saladier.png";
    nb = detectCard(path_sala)*2;
    cout<<nb<<endl;
    if (nb > 20 && nb>nb_max){
        if(nb>50){stop=true;}
        carte_detect = "Saladier";
        nb_max = nb;
    }}

    if(!stop){
        string path_soleil = "../quadrimon/cartes/codes/soleil.png";
        nb = detectCard(path_soleil)/3;
        cout<<nb<<endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "Soleil";
            nb_max = nb;
        }}

    QString card_match_txt=QString::fromStdString(carte_detect);
    ui->nom_carte_label->setText(card_match_txt);
    actualiser_card_match_label(carte_detect);
    setLast_carte_detect(carte_detect);
    cout<<carte_detect<<endl;
}

void Reco_carte::updateImage()
{
    Capture();
    QSize labelSize = ui->capture_label->size();

    Mat resizedFrame;
    cv::resize(captureMat, resizedFrame, cv::Size(labelSize.width(), labelSize.height()));

    QImage img(resizedFrame.data, resizedFrame.cols, resizedFrame.rows, resizedFrame.step, QImage::Format_BGR888);
    QPixmap pixmap = QPixmap::fromImage(img);

    ui->capture_label->setPixmap(pixmap);
}

Reco_carte::Reco_carte(MainWindow *mw_,QWidget *parent)
    : QDialog(parent)
    , mw(mw_)
    , ui(new Ui::Reco_carte)
{
    ui->setupUi(this);
    //connect(this, &Reco_carte::destroyed, this, &Reco_carte::deleteLater);
    capture = VideoCapture(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateImage()));
    timer->start(50); // Interval in milliseconds

}

Reco_carte::~Reco_carte()
{
    delete ui;
}

void Reco_carte::on_capture_button_clicked()
{
    testCartes();
}


void Reco_carte::on_valid_button_clicked()
{
    mw->Set_Carte_trouvee(getLast_carte_detect());
    mw->reco_close();
    close();
}

