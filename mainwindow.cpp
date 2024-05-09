#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reco_carte.h"

#include <QMessageBox>
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
    if (phaseIni<4){
        Reco_carte *r = new Reco_carte(this);
        r->exec();
    } else {
        if (!choix_quad_done){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Changement quadrimon", "Veux tu changer de quadrimon ?",QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                switch_quadri_actif();
            }
            choix_quad_done = !choix_quad_done;

        } else {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Choix attaque", "Veux tu attaquer ?",QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                attaque();
            }
        }
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

    set_inst_txt("Le Joueur tiré au sort pour commencer est : Joueur "+to_string(getEtatJeu())+"\n Il doit enregistrer son premier Quadrimon");
    set_capt_butt_txt("Enregistrer le premier Quadrimon de Joueur "+to_string(getEtatJeu()));

}

void MainWindow::iniquad()
{
    if (phaseIni==1){
        quadrimon q = quadrimon(Get_Carte_trouvee());
        if (!q.getQuad_valid()){
            set_inst_txt("Ton premier Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q.toString());
            if(etatJeu==1){
                ui->J1_quad1_label->setText(txt_temp);
                J1->addQuad1(&q);
            } else if (etatJeu==2){
                ui->J2_quad1_label->setText(txt_temp);
                J2->addQuad1(&q);
            }
            set_inst_txt("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton second Quadrimon");
            set_capt_butt_txt("Enregistrer le second Quadrimon de Joueur "+to_string(getEtatJeu()));

            phaseIni+=1;

        }
    } else if(phaseIni==2){
        quadrimon q = quadrimon(Get_Carte_trouvee());
        if (!q.getQuad_valid()){
            set_inst_txt("Ton second Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q.toString());
            if(etatJeu==1){
                ui->J1_quad2_label->setText(txt_temp);
                J1->addQuad2(&q);
            } else if (etatJeu==2){
                ui->J2_quad2_label->setText(txt_temp);
                J2->addQuad2(&q);
            }
            if (etatJeu==1) {
                etatJeu=2;
            } else if (etatJeu==2){
                etatJeu=1;
            }
            set_inst_txt("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton premier Quadrimon");
            set_capt_butt_txt("Enregistrer le premier Quadrimon de Joueur "+to_string(getEtatJeu()));

            phaseIni+=1;

        }
    } else if (phaseIni==3){
        quadrimon q = quadrimon(Get_Carte_trouvee());
        if (!q.getQuad_valid()){
            set_inst_txt("Ton premier Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q.toString());
            if(etatJeu==1){
                ui->J1_quad1_label->setText(txt_temp);
                J1->addQuad1(&q);

            } else if (etatJeu==2){
                ui->J2_quad1_label->setText(txt_temp);
                J2->addQuad1(&q);

            }
            set_inst_txt("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton second Quadrimon");
            set_capt_butt_txt("Enregistrer le second Quadrimon de Joueur "+to_string(getEtatJeu()));

            phaseIni+=1;
        }
    } else if (phaseIni==4) {
        quadrimon q = quadrimon(Get_Carte_trouvee());
        if (!q.getQuad_valid()){
            set_inst_txt("Ton second Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q.toString());
            if(etatJeu==1){
                ui->J1_quad2_label->setText(txt_temp);
                J1->addQuad2(&q);
            } else if (etatJeu==2){
                ui->J2_quad2_label->setText(txt_temp);
                J2->addQuad2(&q);
            }
            phaseIni+=1;
            if (etatJeu==1) {
                etatJeu=2;
            } else if (etatJeu==2){
                etatJeu=1;
            }
            set_inst_txt(" Joueur "+to_string(getEtatJeu())+ " c'est ton tour");
            set_capt_butt_txt("Changes tu de quadrimon  Joueur "+to_string(getEtatJeu())+" ?");
        }
    }
}

void MainWindow::attaque()
{
    if (etatJeu==1){
        if(J2->est_attaque(J1->degats_a_infliger())){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE
            etatJeu=3;
            set_inst_txt("J1 a gagné \n cliquez 2 fois sur le bouton du bas pour relancer une partie");
            // TODO FIN DE PARTIE AVEC J1 VAINQUEUR
        }
    } else {
        if(J1->est_attaque(J2->degats_a_infliger())){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE
            etatJeu=3;
            set_inst_txt("J1 a gagné \n cliquez 2 fois sur le bouton du bas pour relancer une partie");
            // TODO FIN DE PARTIE AVEC J2 VAINQUEUR
        }
    }
}

void MainWindow::reco_close()
{
    if (!(etatJeu==3)){
        if (!(phaseIni<4)){ //PREMIER BLOCK pour la partie ou on scanne nos 2 quadrimons
            iniquad();
        } else {

        }
    } else {
        set_inst_txt("Le jeu est fini");
        set_capt_butt_txt("Recommancer une partie ? NOT IMPEMENTED YET");
    }

}

void MainWindow::switch_quadri_actif(){
    if (etatJeu==1){
        J1->switchIndexQuadActif1();
    } else {
        J2->switchIndexQuadActif1();
    }
}

void MainWindow::set_inst_txt(string txt_temp)
{
    txt_inst_temp=QString::fromStdString(txt_temp);
    ui->Instruction_label->setText(txt_inst_temp);
}

void MainWindow::set_capt_butt_txt(string txt_temp)
{
    txt_button_temp=QString::fromStdString(txt_temp);
    ui->capture_button->setText(txt_button_temp);
}
