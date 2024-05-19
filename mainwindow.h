#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "iostream"
#include "joueur.h"
#include "terrain.h"

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

    void Set_Carte_trouvee(std::string Ct);
    std::string Get_Carte_trouvee();

    void Set_Terrain_trouvee(std::string Tt);
    std::string Get_Terrain_trouvee();

    int getEtatJeu() const;
    void setEtatJeu(int newEtatJeu);

    void start(); //DETERMINE QUEL JOUEUR COMMENCE
    void restart(); //RECOMMENCE UNE PARTIE
    void iniquad(); // PERMET DE CHARGER LES 2 QUAD DE CHAQUE JOUEUR
    void attaque();

    void reco_close();
    void reco_terrain_close();
    void switch_quadri_actif();
    void switch_tour_joueur();
    void set_inst_txt(std::string txt_temp);
    void set_capt_butt_txt(std::string txt_temp);
    void actualiser_affichage_txt();

private slots:
    void on_capture_button_clicked();

    void on_interrup_J1_button_clicked();

    void on_interrup_J2_button_clicked();

private:
    joueur* J1 = new joueur;
    bool terrain_J1_actif= false;
    joueur* J2 = new joueur;
    bool terrain_J2_actif= false;

    int etatJeu = 0; // 1 = J1 , 2 = J2 , 0 = initial, 3 = fin de partie
    bool J1_gagne = true;
    int phaseIni = 1;// 1 = 1er joueur - 1er quad, 2,...,4 = 2eme joueur - 2eme quad*
    bool premiere_attaque = true;

    bool terrain_a_changer_J1 = true; // true pour changer le terrain de J1 apres une interruption, false pour J2
    Ui::MainWindow *ui;

    std::string Carte_trouvee;
    std::string Terrain_trouvee;
    QString txt_inst_temp;
    QString txt_button_temp;
    bool choix_quad_done = false;

};
#endif // MAINWINDOW_H
