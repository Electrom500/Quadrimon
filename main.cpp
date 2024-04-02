#include "mainwindow.h"
#include "reco_carte.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Reco_carte w;

    w.show();
    return a.exec();
}
