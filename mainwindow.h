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

    int getEtatJeu() const;
    void setEtatJeu(int newEtatJeu);

    void start(); //DETERMINE QUEL JOUEUR COMMENCE
    void iniquad(); // PERMET DE CHARGER LES 2 QUAD DE CHAQUE JOUEUR
    void attaque();

    void reco_close();
    void switch_quadri_actif();
    void set_inst_txt(string txt_temp);
    void set_capt_butt_txt(string txt_temp);
private slots:
    void on_capture_button_clicked();

private:
    joueur* J1;
    joueur* J2;

    int etatJeu = 0; // 1 = J1 , 2 = J2 , 0 = initial, 3 = fin de partie
    int phaseIni = 1;// 1 = 1er joueur - 1er quad, 2,...,4 = 2eme joueur - 2eme quad

    Ui::MainWindow *ui;
    void next_turn();

    string Carte_trouvee;
    QString txt_inst_temp;
    QString txt_button_temp;

    bool choix_quad_done = false;


};
#endif // MAINWINDOW_H
