#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reco_carte.h"

#include <QMessageBox>
#include <QFrame>
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
    if (etatJeu==3){ // PARTIE FIN DE PARTIE
        //restart();
        cout<<"ETAT 3";
    }else if (phaseIni<=4){ // PARTIE INITIALISATION DES QUADRIMONS
        Reco_carte *r = new Reco_carte(this);
        r->exec();
    } else { // TOURS CLASSIQUES
        if (etatJeu==1){

        }

        if (!choix_quad_done){ // PARTIE CHANGEMEENT DE QUAD ACTIF
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Changement quadrimon", "Veux tu changer de quadrimon ?",QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                switch_quadri_actif();
                actualiser_affichage_txt();
            }
            choix_quad_done = !choix_quad_done;
            set_inst_txt(" Joueur "+to_string(getEtatJeu())+ " c'est ton tour \n Veux tu attaquer avec ton quadrimon selectionné ?");
            set_capt_butt_txt("Joueur "+to_string(getEtatJeu())+", à l'attaque ?");

        } else { // PARTIE ATTAQUE CLASSIQUE
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Choix attaque", "Veux tu attaquer ?",QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                attaque();
                actualiser_affichage_txt();
            }
            choix_quad_done = !choix_quad_done;
            switch_tour_joueur();
            set_inst_txt(" Joueur "+to_string(getEtatJeu())+ " c'est ton tour \n Veux tu changer de quadrimon ?");
            set_capt_butt_txt("Changes tu de quadrimon  Joueur "+to_string(getEtatJeu())+" ?");
        }
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

void MainWindow::restart()
{
    etatJeu = 0;
    phaseIni = 1;
    choix_quad_done = false;
    start();
}

void MainWindow::iniquad()
{
    if (phaseIni==1){
        quadrimon q11 = quadrimon(Get_Carte_trouvee());
        if (!q11.getQuad_valid()){
            set_inst_txt("Ton premier Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q11.toString());
            if(etatJeu==1){
                ui->J1_quad1_label->setText(txt_temp);
                J1->addQuad1(new quadrimon(Get_Carte_trouvee()));

            } else if (etatJeu==2){
                ui->J2_quad1_label->setText(txt_temp);
                J2->addQuad1(new quadrimon(Get_Carte_trouvee()));

            }
            set_inst_txt("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton second Quadrimon");
            set_capt_butt_txt("Enregistrer le second Quadrimon de Joueur "+to_string(getEtatJeu()));

            phaseIni+=1;
        }
    } else if(phaseIni==2){
        quadrimon q12 = quadrimon(Get_Carte_trouvee());
        if (!q12.getQuad_valid()){
            set_inst_txt("Ton second Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q12.toString());
            if(etatJeu==1){
                ui->J1_quad2_label->setText(txt_temp);
                J1->addQuad2(new quadrimon(Get_Carte_trouvee()));

            } else if (etatJeu==2){
                ui->J2_quad2_label->setText(txt_temp);
                J2->addQuad2(new quadrimon(Get_Carte_trouvee()));

            }
            switch_tour_joueur();
            set_inst_txt("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton premier Quadrimon");
            set_capt_butt_txt("Enregistrer le premier Quadrimon de Joueur "+to_string(getEtatJeu()));

            phaseIni+=1;

        }
    } else if (phaseIni==3){
        quadrimon q21 = quadrimon(Get_Carte_trouvee());
        if (!q21.getQuad_valid()){
            set_inst_txt("Ton premier Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q21.toString());
            if(etatJeu==1){
                ui->J1_quad1_label->setText(txt_temp);
                J1->addQuad1(new quadrimon(Get_Carte_trouvee()));

            } else if (etatJeu==2){
                ui->J2_quad1_label->setText(txt_temp);
                J2->addQuad1(new quadrimon(Get_Carte_trouvee()));

            }
            set_inst_txt("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton second Quadrimon");
            set_capt_butt_txt("Enregistrer le second Quadrimon de Joueur "+to_string(getEtatJeu()));

            phaseIni+=1;
        }
    } else if (phaseIni==4) {
        quadrimon q22 = quadrimon(Get_Carte_trouvee());
        if (!q22.getQuad_valid()){
            set_inst_txt("Ton second Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q22.toString());
            if(etatJeu==1){
                ui->J1_quad2_label->setText(txt_temp);
                J1->addQuad2(new quadrimon(Get_Carte_trouvee()));

            } else if (etatJeu==2){
                ui->J2_quad2_label->setText(txt_temp);
                J2->addQuad2(new quadrimon(Get_Carte_trouvee()));

            }
            phaseIni+=1;
            switch_tour_joueur();
            set_inst_txt(" Joueur "+to_string(getEtatJeu())+ " c'est ton tour");
            set_capt_butt_txt("Changes tu de quadrimon  Joueur "+to_string(getEtatJeu())+" ?");
            if(!J1->getIndexQuadActif1()){
                J1->switchIndexQuadActif1();
            }
            actualiser_affichage_txt();
        }
    }
}

void MainWindow::attaque()
{
    if (etatJeu==1){
        if(J2->est_attaque(J1->degats_a_infliger())){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE
            etatJeu=3;
            set_inst_txt("J1 a gagné \n cliquez sur le bouton du bas pour relancer une partie");
            // TODO FIN DE PARTIE AVEC J1 VAINQUEUR
        }
    } else {
        if(J1->est_attaque(J2->degats_a_infliger())){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE
            etatJeu=3;
            set_inst_txt("J1 a gagné \n cliquez sur le bouton du bas pour relancer une partie");
            // TODO FIN DE PARTIE AVEC J2 VAINQUEUR
        }
    }
    actualiser_affichage_txt();
}

void MainWindow::reco_close()
{
    if (!(etatJeu==3)){
        if (phaseIni<=4){ //PREMIER BLOCK pour la partie ou on scanne nos 2 quadrimons
            iniquad();
        }
    } else {
        set_inst_txt("Le jeu est fini");
        set_capt_butt_txt("Recommancer une partie ? NOT IMPEMENTED YET");
    }
}

void MainWindow::switch_quadri_actif(){
    if (etatJeu==1){
        cout<<"etat actif J1 = "+to_string(J1->getIndexQuadActif1())<<endl;
        J1->switchIndexQuadActif1();
        cout<<"etat actif J1 = "+to_string(J1->getIndexQuadActif1())<<endl;
    } else {
        cout<<"etat actif J2 = "+to_string(J2->getIndexQuadActif1())<<endl;
        J2->switchIndexQuadActif1();
        cout<<"etat actif J2 = "+to_string(J2->getIndexQuadActif1())<<endl;
    }
    actualiser_affichage_txt();
}

void MainWindow::switch_tour_joueur()
{
    if (etatJeu==1) {
        etatJeu=2;
    } else if (etatJeu==2){
        etatJeu=1;
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

void MainWindow::actualiser_affichage_txt()
{
    // "Affichage" des quad de j1
    QString txt_temp=QString::fromStdString(J1->get_q1_txt());
    ui->J1_quad1_label->setText(txt_temp);
    txt_temp=QString::fromStdString(J1->get_q2_txt());
    ui->J1_quad2_label->setText(txt_temp);

    // "Affichage" des quad de j2
    txt_temp=QString::fromStdString(J2->get_q1_txt());
    ui->J2_quad1_label->setText(txt_temp);
    txt_temp=QString::fromStdString(J2->get_q2_txt());
    ui->J2_quad2_label->setText(txt_temp);

    if(J1->getIndexQuadActif1()){ //IDENTIFICATION DU QUADRIMON ACTIF DE J1
        ui->J1_quad1_label->setFrameShape(QFrame::Box);
        ui->J1_quad2_label->setFrameShape(QFrame::NoFrame);
    } else {
        ui->J1_quad2_label->setFrameShape(QFrame::Box);
        ui->J1_quad1_label->setFrameShape(QFrame::NoFrame);
    }

    if(J2->getIndexQuadActif1()){ //IDENTIFICATION DU QUADRIMON ACTIF DE J2
        ui->J2_quad1_label->setFrameShape(QFrame::Box);
        ui->J2_quad2_label->setFrameShape(QFrame::NoFrame);
    } else {
        ui->J2_quad2_label->setFrameShape(QFrame::Box);
        ui->J2_quad1_label->setFrameShape(QFrame::NoFrame);
    }
}
