#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reco_carte.h"
#include "reco_terrain.h"

#include <QMessageBox>
#include <QFrame>
#include <random>
#include <iostream>



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
        restart();
    }else if (phaseIni<=4){ // PARTIE INITIALISATION DES QUADRIMONS
        Reco_carte *r = new Reco_carte(this);
        // Reco_terrain *r = new Reco_terrain(this); // POUR TESTER LA RECONNAISSANCE DES TERRRAINS
        r->exec();
    } else { // TOURS CLASSIQUES

        // PARTIE UTILISATION DES TERRAINS
        if (terrain_J1_actif){
            if (J1->getTerrainActif()->getEffet_spe()){
                if(J1->est_attaque(J1->getTerrainActif()->getValue(),10)){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE + type a 10 pour être sur de ne pas activer d'avantage de type
                    etatJeu=3;
                    set_inst_txt("J1 a gagné ! \n cliquez sur le bouton du bas pour relancer une partie");
                    set_capt_butt_txt(" Restart ");
                    J1_gagne = false;
                }
            } else { // TODO
                if(J1->getTerrainActif()->getName()=="grotte"){
                    choix_quad_done = true;
                } else if (J1->getTerrainActif()->getName()=="toile"){

                }else if (J1->getTerrainActif()->getName()=="chat"){

                }else if (J1->getTerrainActif()->getName()=="volcan"){

                }else if (J1->getTerrainActif()->getName()=="foret"){

                }else{ // Plage

                }
            }
            if (J1->getTerrainActif()->reduc_tour()){
                terrain_J1_actif = false;
            }
        }


        if (!choix_quad_done){ // PARTIE CHANGEMENT DE QUAD ACTIF
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Changement quadrimon", "Veux tu changer de quadrimon ?",QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                switch_quadri_actif();
                actualiser_affichage_txt(); // ACTUALISE LE CADRE DE SELECTION DE QUADRI
            }
            choix_quad_done = true;
            set_inst_txt(" Joueur "+std::__cxx11::to_string(getEtatJeu())+ " c'est ton tour \n Veux tu attaquer avec ton quadrimon selectionné ?");
            set_capt_butt_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", à l'attaque ?");

        } else { // PARTIE ATTAQUE CLASSIQUE
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Choix attaque", "Veux tu attaquer ?",QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                bool q_switch_ko;
                if (etatJeu==1) {
                    q_switch_ko = J1->getIndexQuadActif1();
                } else {
                    q_switch_ko = J2->getIndexQuadActif1();
                }
                attaque();
                if (etatJeu==1) {
                    if (q_switch_ko != J1->getIndexQuadActif1()){
                        J1->switchIndexQuadActif1();
                    }
                    ui->openGLWidget->attaqueQuadJ1();
                } else {
                    if (q_switch_ko != J2->getIndexQuadActif1()){
                        J2->switchIndexQuadActif1();
                    }
                    ui->openGLWidget->attaqueQuadJ2();
                }

                actualiser_affichage_txt();
            }
            if (etatJeu!=3){
                choix_quad_done = false;
                switch_tour_joueur();
                set_inst_txt(" Joueur "+std::__cxx11::to_string(getEtatJeu())+ " c'est ton tour \n Veux tu changer de quadrimon ?");
                set_capt_butt_txt("Changes tu de quadrimon  Joueur "+std::__cxx11::to_string(getEtatJeu())+" ?");
            }

            if (etatJeu==1){
                if (J1->getQ1_ko() || J1->getQ2_ko()){
                    choix_quad_done = true;
                    set_inst_txt(" Joueur "+std::__cxx11::to_string(getEtatJeu())+ " c'est ton tour \n Veux tu attaquer avec ton quadrimon selectionné ?");
                    set_capt_butt_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", à l'attaque ?");
                }
            } else if (etatJeu==2) {
                if (J2->getQ1_ko() || J2->getQ2_ko()){
                    choix_quad_done = true;
                    set_inst_txt(" Joueur "+std::__cxx11::to_string(getEtatJeu())+ " c'est ton tour \n Veux tu attaquer avec ton quadrimon selectionné ?");
                    set_capt_butt_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", à l'attaque ?");
                }
            }
            if (premiere_attaque){
                if (getEtatJeu()==1){
                    ui->interrup_J2_button->setEnabled(true);
                } else {
                    ui->interrup_J1_button->setEnabled(true);
                }
                premiere_attaque=false;
            }
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

void MainWindow::Set_Carte_trouvee(std::string Ct){
    Carte_trouvee = Ct;
}

std::string MainWindow::Get_Carte_trouvee(){
    return Carte_trouvee;
}

void MainWindow::Set_Terrain_trouvee(std::string Tt)
{
    Terrain_trouvee = Tt;
}

std::string MainWindow::Get_Terrain_trouvee()
{
    return Terrain_trouvee;
}

void MainWindow::start(){
    // Partie Nombre aléatoire pour déterminer le joueur qui commence
    std::random_device rd;
    std::mt19937 generator(rd()); // Générateur Mersenne Twister 19937
    std::uniform_int_distribution<int> distribution(1,2);
    setEtatJeu(distribution(generator));

    set_inst_txt("Le Joueur tiré au sort pour commencer est : Joueur "+std::__cxx11::to_string(getEtatJeu())+"\n Il doit enregistrer son premier Quadrimon");
    set_capt_butt_txt("Enregistrer le premier Quadrimon de Joueur "+std::__cxx11::to_string(getEtatJeu()));
    if (getEtatJeu()==1){
        ui->interrup_J1_button->setEnabled(false);
    } else {
        ui->interrup_J2_button->setEnabled(false);
    }
}

void MainWindow::restart()
{
    delete J1;
    delete J2;
    J1 = new joueur;
    J2 = new joueur;
    etatJeu = 0;
    phaseIni = 1;
    choix_quad_done = false;
    actualiser_affichage_txt();
    start();
}

void MainWindow::iniquad()
{
    if (phaseIni==1){
        quadrimon q11 = quadrimon(Get_Carte_trouvee());
        if (!q11.getQuad_valid()){
            set_inst_txt("Ton premier Quadrimon n'a été reconnu, \n Joueur "+std::__cxx11::to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q11.toString());
            if(etatJeu==1){
                ui->J1_quad1_label->setText(txt_temp);
                J1->addQuad1(new quadrimon(Get_Carte_trouvee()));

            } else if (etatJeu==2){
                ui->J2_quad1_label->setText(txt_temp);
                J2->addQuad1(new quadrimon(Get_Carte_trouvee()));

            }
            set_inst_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", tu dois enregistrer ton second Quadrimon");
            set_capt_butt_txt("Enregistrer le second Quadrimon de Joueur "+std::__cxx11::to_string(getEtatJeu()));

            phaseIni+=1;
        }
    } else if(phaseIni==2){
        quadrimon q12 = quadrimon(Get_Carte_trouvee());
        if (!q12.getQuad_valid()){
            set_inst_txt("Ton second Quadrimon n'a été reconnu, \n Joueur "+std::__cxx11::to_string(getEtatJeu())+" recommence !");
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
            set_inst_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", tu dois enregistrer ton premier Quadrimon");
            set_capt_butt_txt("Enregistrer le premier Quadrimon de Joueur "+std::__cxx11::to_string(getEtatJeu()));

            phaseIni+=1;

        }
    } else if (phaseIni==3){
        quadrimon q21 = quadrimon(Get_Carte_trouvee());
        if (!q21.getQuad_valid()){
            set_inst_txt("Ton premier Quadrimon n'a été reconnu, \n Joueur "+std::__cxx11::to_string(getEtatJeu())+" recommence !");
        } else {
            QString txt_temp=QString::fromStdString(q21.toString());
            if(etatJeu==1){
                ui->J1_quad1_label->setText(txt_temp);
                J1->addQuad1(new quadrimon(Get_Carte_trouvee()));

            } else if (etatJeu==2){
                ui->J2_quad1_label->setText(txt_temp);
                J2->addQuad1(new quadrimon(Get_Carte_trouvee()));

            }
            set_inst_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", tu dois enregistrer ton second Quadrimon");
            set_capt_butt_txt("Enregistrer le second Quadrimon de Joueur "+std::__cxx11::to_string(getEtatJeu()));

            phaseIni+=1;
        }
    } else if (phaseIni==4) {
        quadrimon q22 = quadrimon(Get_Carte_trouvee());
        if (!q22.getQuad_valid()){
            set_inst_txt("Ton second Quadrimon n'a été reconnu, \n Joueur "+std::__cxx11::to_string(getEtatJeu())+" recommence !");
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
            set_inst_txt(" Joueur "+std::__cxx11::to_string(getEtatJeu())+ " c'est ton tour");
            set_capt_butt_txt("Changes tu de quadrimon  Joueur "+std::__cxx11::to_string(getEtatJeu())+" ?");
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
        if(J2->est_attaque(J1->degats_a_infliger(),J1->get_type_attaque())){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE
            etatJeu=3;
            set_inst_txt("J1 a gagné ! \n cliquez sur le bouton du bas pour relancer une partie");
            set_capt_butt_txt(" Restart ");
            J1_gagne = true;
        }
    } else {
        if(J1->est_attaque(J2->degats_a_infliger(),J2->get_type_attaque())){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE
            etatJeu=3;
            set_inst_txt("J1 a gagné ! \n cliquez sur le bouton du bas pour relancer une partie");
            set_capt_butt_txt(" Restart ");
            J1_gagne = false;
        }
    }
    actualiser_affichage_txt();
}

void MainWindow::reco_close()
{
    if (phaseIni<=4){ //PREMIER BLOCK pour la partie ou on scanne nos 2 quadrimons
        iniquad();
    }
}

void MainWindow::reco_terrain_close()
{
    terrain *t = new terrain(Get_Terrain_trouvee());
    if (t->getTerrain_valid()){
        if (terrain_a_changer_J1){
            J1->setTerrainActif(t);
            terrain_J1_actif = true;
        }else{
            J2->setTerrainActif(t);
            terrain_J1_actif = true;
        }
    }
}

void MainWindow::switch_quadri_actif(){
    if (etatJeu==1){
        J1->switchIndexQuadActif1();
    } else {
        J2->switchIndexQuadActif1();
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

void MainWindow::set_inst_txt(std::string txt_temp)
{
    txt_inst_temp=QString::fromStdString(txt_temp);
    ui->Instruction_label->setText(txt_inst_temp);
}

void MainWindow::set_capt_butt_txt(std::string txt_temp)
{
    txt_button_temp=QString::fromStdString(txt_temp);
    ui->capture_button->setText(txt_button_temp);
}

void MainWindow::actualiser_affichage_txt()
{
    // Affichage des quad de j1
    QString txt_temp=QString::fromStdString(J1->get_q1_txt());
    ui->J1_quad1_label->setText(txt_temp);
    txt_temp=QString::fromStdString(J1->get_q2_txt());
    ui->J1_quad2_label->setText(txt_temp);
    ui->openGLWidget->changeQuadJ1(J1->getNameQuadActif());
    ui->openGLWidget->changeTerrJ1(J1->getTerrainActif()->getName());
    ui->openGLWidget->attaqueQuadJ1();

    // Affichage des quad de j2
    txt_temp=QString::fromStdString(J2->get_q1_txt());
    ui->J2_quad1_label->setText(txt_temp);
    txt_temp=QString::fromStdString(J2->get_q2_txt());
    ui->J2_quad2_label->setText(txt_temp);
    ui->openGLWidget->changeQuadJ2(J2->getNameQuadActif());
    ui->openGLWidget->changeTerrJ2(J2->getTerrainActif()->getName());

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

void MainWindow::on_interrup_J1_button_clicked()
{
    terrain_a_changer_J1 = true;
    Reco_terrain *r = new Reco_terrain(this);
    r->exec();
}

void MainWindow::on_interrup_J2_button_clicked()
{
    terrain_a_changer_J1 = false;
    Reco_terrain *r = new Reco_terrain(this);
    r->exec();
}

