#include "reco_terrain.h"
#include "ui_reco_terrain.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include "QTimer"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"

using namespace cv;

int Reco_terrain::detectCard(std::string path)
{
    if (!captureMat.empty()){
        Mat img1 = imread(path, IMREAD_GRAYSCALE);
        Mat img2 = captureMat;
        if ( img1.empty() )
        {
            std::cout << "Could not open or find the image!\n "<< std::endl;
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
        //cout<<"Il y a : "<< good_matches.size()<< "good matches "<<std::endl;
        return good_matches.size();
    }
    return 0;

}


void Reco_terrain::Capture()

{
    if(!capture.isOpened())
    {
        std::cerr<<"Error opening the default camera"<<std::endl;
    }

    Mat frame;

    capture >> frame; //new frame from camera

    // check if the frame is empty
    if (frame.empty()) {
        std::cerr << "Error: Captured frame is empty" << std::endl;

    }

    captureMat = frame;
    //imshow("test",frame);
}
void Reco_terrain::charger_image(QString cheminImage) {
    // Charge l'image et la redimentionne


    QImage image(cheminImage);
    //QSize tailleTest(100, 100); Test
    QSize tailleLabel = ui->card_match_label->size();

    image = image.scaled(tailleLabel, Qt::KeepAspectRatio); // Garder le ratio d'aspect

    ui->card_match_label->setPixmap(QPixmap::fromImage(image));
}

std::string Reco_terrain::getLast_carte_detect() const
{
    return last_carte_detect;
}

void Reco_terrain::setLast_carte_detect(const std::string &newLast_carte_detect)
{
    last_carte_detect = newLast_carte_detect;
}

void Reco_terrain::actualiser_card_match_label(std::string carte_detect){
    std::string path ="../../cartes/codes/";
    path+=carte_detect+".png";

    if (path != ""){
        QString Qpath=QString::fromStdString(path);
        charger_image(Qpath);
    } else {
        // TODO ????
    }
}

void Reco_terrain::testCartes(){

    int nb_max = 0;
    bool stop = false;
    float corr;

    std::string path ="../../cartes/codes/";
    std::string path_cyl = path + "chat.png";
    corr = 0.7;
    int nb = detectCard(path_cyl)*corr;
    std::cout<<nb<<std::endl;
    std::string carte_detect = "None";
    if (nb > 20) {
        if(nb>50){stop=true;}
        carte_detect = "chat";
        nb_max = nb;
    }

    if(!stop){
        std::string path_gizeh = path + "foret.png";
        corr = 0.4;
        nb = detectCard(path_gizeh)*corr;
        std::cout<<nb<<std::endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "foret";
            nb_max = nb;
        }
    }

    if(!stop){
        std::string path_flamby = path + "grotte.png";
        corr = 0.3;
        nb = detectCard(path_flamby)*corr;
        std::cout<<nb<<std::endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "grotte";
            nb_max = nb;
        }
    }

    if(!stop){
        std::string path_glace = path + "infirmerie.png";
        corr = 0.3;
        nb = detectCard(path_glace)*corr;
        std::cout<<nb<<std::endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "infirmerie";
            nb_max = nb;
        }
    }

    if(!stop){
        std::string path_khone = path + "marais.png";
        corr = 0.4;
        nb = detectCard(path_khone)*corr;
        std::cout<<nb<<std::endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "marais";
            nb_max = nb;
        }
    }

    if(!stop){
        std::string path_menu = path + "ouragan.png";
        corr = 0.;
        nb = detectCard(path_menu)*corr;
        std::cout<<nb<<std::endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "ouragan";
            nb_max = nb;
        }
    }

    if(!stop){
        std::string path_olaf = path + "plage.png";
        corr = 0.5;
        nb = detectCard(path_olaf)*corr;
        std::cout<<nb<<std::endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "plage";
            nb_max = nb;
        }
    }

    if(!stop){
        std::string path_sala = path + "toile.png";
        corr = 0.1;
        nb = detectCard(path_sala)*corr;
        std::cout<<nb<<std::endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "toile";
            nb_max = nb;
        }
    }

    if(!stop){
        std::string path_soleil = path + "volcan.png";
        corr = 0.2;
        nb = detectCard(path_soleil)*corr;
        std::cout<<nb<<std::endl;
        if (nb > 20 && nb>nb_max){
            if(nb>50){stop=true;}
            carte_detect = "volcan";
            nb_max = nb;
        }
    }

    QString card_match_txt=QString::fromStdString(carte_detect);
    ui->nom_carte_label->setText(card_match_txt);
    actualiser_card_match_label(carte_detect);
    setLast_carte_detect(carte_detect);
    std::cout<<carte_detect<<std::endl;
}

void Reco_terrain::updateImage()
{
    if(capture.isOpened()){
        Capture();
        QSize labelSize = ui->capture_label->size();

        Mat resizedFrame;
        cv::resize(captureMat, resizedFrame, cv::Size(labelSize.width(), labelSize.height()));

        QImage img(resizedFrame.data, resizedFrame.cols, resizedFrame.rows, resizedFrame.step, QImage::Format_BGR888);
        QPixmap pixmap = QPixmap::fromImage(img);

        ui->capture_label->setPixmap(pixmap);
    }
}

Reco_terrain::Reco_terrain(MainWindow *mw_,QWidget *parent)
    : QDialog(parent)
    , mw(mw_)
    , ui(new Ui::Reco_terrain)
{
    ui->setupUi(this);
    capture = VideoCapture(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateImage()));
    timer->start(50); // Interval in milliseconds

}

Reco_terrain::~Reco_terrain()
{
    delete ui;
}

void Reco_terrain::on_capture_button_clicked()
{
    testCartes();
}

void Reco_terrain::on_valid_button_clicked()
{
    mw->Set_Terrain_trouvee(getLast_carte_detect());
    mw->reco_terrain_close();
    capture.release();
    close();
}
