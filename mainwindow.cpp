#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reco_carte.h"
#include "reco_terrain.h"

#include <QMessageBox>
#include <QFrame>
#include <random>
#include <iostream>
#include <QDir>

// -------------------- BASICS--------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    QDir dir("./");
    std::string a = dir.absolutePath().toStdString();
    std::cout<<a;
    ui->setupUi(this);
    start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// -------------------------------RE.INITIALISATION------------------------------
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
    actualiser_affichage_txt();
    ui->openGLWidget->changeTerrJ1("");
    ui->openGLWidget->changeTerrJ2("");
    etatJeu = 0;
    phaseIni = 1;
    choix_quad_done = false;


    start();
}

//---------------------------PHASES DE JEU--------------------------

void MainWindow::on_capture_button_clicked()
{
    if (etatJeu==3){ // PARTIE FIN DE PARTIE
        restart();
    }else if (phaseIni<=4){ // PARTIE INITIALISATION DES QUADRIMONS
        Reco_carte *r = new Reco_carte(this);
        r->exec();
    } else { // TOURS CLASSIQUES

        if (!terrain_deja_jouer){ // PARTIE TERRAINS
            if(etatJeu==1){
                int result;
                if(J2->getTerrainInitialized()){
                    result = J1->effet_terrain(true,J2->getTerrainActif());
                } else {
                    result = J1->effet_terrain(false,nullptr);
                }

                if(result ==1){
                    etatJeu=3;
                    set_inst_txt("J2 a gagné ! \n cliquez sur le bouton du bas pour relancer une partie");
                    set_capt_butt_txt(" Restart ");
                    J1_gagne = false;
                } else if (result ==2){
                    choix_quad_done = true;
                }
            }else{
                int result;
                if(J1->getTerrainInitialized()){
                    result = J2->effet_terrain(true,J1->getTerrainActif());
                } else {
                    result = J2->effet_terrain(false,nullptr);
                }

                if(result ==1){
                    etatJeu=3;
                    set_inst_txt("J1 a gagné ! \n cliquez sur le bouton du bas pour relancer une partie");
                    set_capt_butt_txt(" Restart ");
                    J1_gagne = true;
                } else if (result ==2){
                    choix_quad_done = true;
                }
            }
            terrain_deja_jouer = true;
            actualiser_affichage_txt();
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
            terrain_deja_jouer = false;
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
                } else {
                    if (q_switch_ko != J2->getIndexQuadActif1()){
                        J2->switchIndexQuadActif1();
                    }
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
                if(J1->getTerrainInitialized()){
                    if(J1->getTerrainActif()->getName()== "grotte" && J1->getTerrainActif()->getTerrain_enable()){
                        set_inst_txt(" Joueur "+std::__cxx11::to_string(getEtatJeu())+ " c'est ton tour \n Veux tu attaquer avec ton quadrimon selectionné ?");
                        set_capt_butt_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", à l'attaque ?");
                        J1->getTerrainActif()->reduc_tour();
                    }
                }
            } else if (etatJeu==2) {
                if (J2->getQ1_ko() || J2->getQ2_ko()){
                    choix_quad_done = true;
                    set_inst_txt(" Joueur "+std::__cxx11::to_string(getEtatJeu())+ " c'est ton tour \n Veux tu attaquer avec ton quadrimon selectionné ?");
                    set_capt_butt_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", à l'attaque ?");
                }
                if(J2->getTerrainInitialized()){
                    if(J2->getTerrainActif()->getName()== "grotte" && J2->getTerrainActif()->getTerrain_enable()){
                        set_inst_txt(" Joueur "+std::__cxx11::to_string(getEtatJeu())+ " c'est ton tour \n Veux tu attaquer avec ton quadrimon selectionné ?");
                        set_capt_butt_txt("Joueur "+std::__cxx11::to_string(getEtatJeu())+", à l'attaque ?");
                        J1->getTerrainActif()->reduc_tour();
                    }
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


void MainWindow::iniquad() //PHASE D INITIALISATION DES 4 QUADRIMONS
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
        ui->openGLWidget->getQuadD()->attaque();
        if(J2->est_attaque(J1->degats_a_infliger(),J1->get_type_attaque())){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE
            etatJeu=3;
            set_inst_txt("J1 a gagné ! \n cliquez sur le bouton du bas pour relancer une partie");
            set_capt_butt_txt(" Restart ");
            J1_gagne = true;
        }
    } else {
        ui->openGLWidget->getQuadD()->attaque();
        if(J1->est_attaque(J2->degats_a_infliger(),J2->get_type_attaque())){ // ATTAQUE ET VERIFIE LA FIN DE PARTIE
            etatJeu=3;
            set_inst_txt("J1 a gagné ! \n cliquez sur le bouton du bas pour relancer une partie");
            set_capt_butt_txt(" Restart ");
            J1_gagne = false;
        }
    }
    actualiser_affichage_txt();
}

// --------------------------FERMETURE DE FENETRE---------------------------------

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
            //J1->
        }else{
            J2->setTerrainActif(t);
        }
        actualiser_affichage_txt();
    } else {
        std::cout<< " TERRAIN INVALIDE ?"<<std::endl;
    }

}

// ------------------------------SWITCH-----------------------------------

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

// ----------------------------AFFICHAGE --------------------------

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
    QString txt_temp;
    if (phaseIni>3)  {
        // Affichage des quad de j1
        txt_temp=QString::fromStdString(J1->get_q1_txt());
        ui->J1_quad1_label->setText(txt_temp);
        txt_temp=QString::fromStdString(J1->get_q2_txt());
        ui->J1_quad2_label->setText(txt_temp);

        // Affichage du terrain de j1
        ui->openGLWidget->changeQuadJ1(J1->getNameQuadActif());
        if(J1->getTerrainInitialized()){
            if(J1->getTerrainActif()->getTerrain_enable()){ //Pour ne pas afficher les terrains qui ont expiré
                ui->openGLWidget->changeTerrJ1(J1->getTerrainActif()->getName());
            } else {
                ui->openGLWidget->changeTerrJ1("");
            }
        }

        // Affichage des quad de j2
        txt_temp=QString::fromStdString(J2->get_q1_txt());
        ui->J2_quad1_label->setText(txt_temp);
        txt_temp=QString::fromStdString(J2->get_q2_txt());
        ui->J2_quad2_label->setText(txt_temp);

        // Affichage du terrain de j2
        ui->openGLWidget->changeQuadJ2(J2->getNameQuadActif());
        if(J2->getTerrainInitialized()){
            if(J2->getTerrainActif()->getTerrain_enable()){
                ui->openGLWidget->changeTerrJ2(J2->getTerrainActif()->getName());
            } else {
                ui->openGLWidget->changeTerrJ2("");
            }
        }

         //IDENTIFICATION DU QUADRIMON ACTIF DE J1
        if(J1->getIndexQuadActif1()){
            ui->J1_quad1_label->setFrameShape(QFrame::Box);
            ui->J1_quad2_label->setFrameShape(QFrame::NoFrame);
        } else {
            ui->J1_quad2_label->setFrameShape(QFrame::Box);
            ui->J1_quad1_label->setFrameShape(QFrame::NoFrame);
        }

        //IDENTIFICATION DU QUADRIMON ACTIF DE J2
        if(J2->getIndexQuadActif1()){
            ui->J2_quad1_label->setFrameShape(QFrame::Box);
            ui->J2_quad2_label->setFrameShape(QFrame::NoFrame);
        } else {
            ui->J2_quad2_label->setFrameShape(QFrame::Box);
            ui->J2_quad1_label->setFrameShape(QFrame::NoFrame);
        }
    }

    //LABEL DU TERRAIN ACTIF DE J1
    std::string string_temp = "";
    if(J1->getTerrainInitialized()){
        if(J1->getTerrainActif()->getTerrain_enable()){
            string_temp = J1->getTerrainActif()->getName();
            if(J1->getTerrainActif()->getNb_tours()==-1){
                string_temp += "\n Terrain permanent";
            }else{
                string_temp += "\n Nombre de tours restant : " + std::to_string(J1->getTerrainActif()->getNb_tours());
            }
        } else {
            string_temp = " Aucun !";
        }
    }else {
        string_temp = " Aucun !";
    }
    txt_temp=QString::fromStdString("Terrain actif : "+string_temp);
    ui->J1_terrain_label->setText(txt_temp);

    //LABEL DU TERRAIN ACTIF DE J2
    if(J2->getTerrainInitialized()){
        if(J2->getTerrainActif()->getTerrain_enable()){
            string_temp = J2->getTerrainActif()->getName();
            if(J2->getTerrainActif()->getNb_tours()==-1){
                string_temp += "\n Terrain permanent";
            }else{
                string_temp += "\n Nombre de tours restant : " + std::to_string(J2->getTerrainActif()->getNb_tours());
            }
        } else {
            string_temp = " Aucun !";
        }
    }else {
        string_temp = " Aucun !";
    }
    txt_temp=QString::fromStdString("Terrain actif : "+string_temp);
    ui->J2_terrain_label->setText(txt_temp);
}



// ------------------------------GETTER ET SETTER -------------------------------

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

// -----------------------------INTERRUPTIONS --------------------------------

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

