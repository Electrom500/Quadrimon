#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reco_carte.h"


#include <random>
#include <iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_capture_button_clicked()
{
    if (phaseIni){
        Reco_carte *w = new Reco_carte(this);
        w->exec();
    } else {
        Reco_carte *w = new Reco_carte(this);
        w->exec();
        next_turn();
    }
}



int MainWindow::getEtatJeu() const
{
    return etatJeu;
}

void MainWindow::setEtatJeu(int newEtatJeu)
{
    etatJeu = newEtatJeu;
}

void MainWindow::next_turn(){

};
void MainWindow::Actualiser_Info_J1(){
    QString txt_temp=QString::fromStdString("");
    ui->J1_info_label->setText(txt_temp);
}
void MainWindow::Set_Carte_trouvee(string Ct){
    Carte_trouvee = Ct;
}

string MainWindow::Get_Carte_trouvee(){
    return Carte_trouvee;
}

void MainWindow::start(){
    // Partie Nombre aléatoire pour déterminer le joueur qui commence
    random_device rd;
    mt19937 generator(rd()); // Générateur Mersenne Twister 19937
    uniform_int_distribution<int> distribution(1,2);
    setEtatJeu(distribution(generator));

    txt_inst_temp=QString::fromStdString("Le Joueur tiré au sort pour commencer est : Joueur "+to_string(getEtatJeu()));
    txt_button_temp=QString::fromStdString("Enregistrer le premier Quadrimon de Joueur "+to_string(getEtatJeu()));
    ui->Instruction_label->setText(txt_inst_temp);
    ui->capture_button->setText(txt_button_temp);
}

int MainWindow::charge_quad()
{

}

void MainWindow::reco_close()
{
    if (phaseIni){
        quadrimon q1 = quadrimon(Get_Carte_trouvee());
        if (!q1.getQuad_valid()){
            txt_inst_temp=QString::fromStdString("Aucun Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
            ui->Instruction_label->setText(txt_inst_temp);
        } else {
            QString txt_temp=QString::fromStdString("Le quadrimon choisi a comme PV :  "+to_string(q1.getPv()));
            ui->J1_info_label->setText(txt_temp);
        }
    }
}

