#include "mainwindow.h"
#include "reco_carte.h"
#include <QApplication>
#include <QDir>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
