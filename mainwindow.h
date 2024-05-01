#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "iostream"
#include "joueur.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void Set_Carte_trouvee(string Ct);
    void Actualiser_Info_J1();
    string Get_Carte_trouvee();
    bool getPremierTour() const;
    void setPremierTour(bool newPremierTour);

    int getEtatJeu() const;
    void setEtatJeu(int newEtatJeu);

private slots:
    void on_capture_button_clicked();

private:
    joueur* J1;
    joueur* J2;
    int etatJeu = 0;
    bool premierTour = true;
    Ui::MainWindow *ui;
    void next_turn();

    string Carte_trouvee;


};
#endif // MAINWINDOW_H
