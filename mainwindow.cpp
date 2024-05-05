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
        Reco_carte *r = new Reco_carte(this);
        r->exec();
    } else {
        Reco_carte *r = new Reco_carte(this);
        r->exec();
       //-------------------- changer ça -------------
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

    txt_inst_temp=QString::fromStdString("Le Joueur tiré au sort pour commencer est : Joueur "+to_string(getEtatJeu())+"\n Il doit enregistrer son premier Quadrimon");
    txt_button_temp=QString::fromStdString("Enregistrer le premier Quadrimon de Joueur "+to_string(getEtatJeu()));
    ui->Instruction_label->setText(txt_inst_temp);
    ui->capture_button->setText(txt_button_temp);

}

int MainWindow::charge_quad()
{
    return 0;
}

void MainWindow::reco_close()
{
    //PREMIER BLOCK DE IF PHASEINI Pour la partie ou on scanne nos 2 quadrimons
    quadrimon q = quadrimon("Glace");
    if (phaseIni==1){
        quadrimon q1 = quadrimon(Get_Carte_trouvee());
        if (!q1.getQuad_valid()){
            txt_inst_temp=QString::fromStdString("Ton premier Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
            ui->Instruction_label->setText(txt_inst_temp);
        } else {
            QString txt_temp=QString::fromStdString(q1.toString());
            if(etatJeu==1){
                ui->J1_quad1_label->setText(txt_temp);
                J1->addQuad1(q);
                cout<<"--- J1 quad 1 ---"<<endl;
            } else if (etatJeu==2){
                ui->J2_quad1_label->setText(txt_temp);
                J2->addQuad1(q);
                cout<<"--- J2 quad 1 ---"<<endl;
            }
            txt_inst_temp=QString::fromStdString("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton second Quadrimon");
            txt_button_temp=QString::fromStdString("Enregistrer le second Quadrimon de Joueur "+to_string(getEtatJeu()));
            ui->Instruction_label->setText(txt_inst_temp);
            ui->capture_button->setText(txt_button_temp);
            phaseIni+=1;

        }
    } else if(phaseIni==2){
        quadrimon q2 = quadrimon(Get_Carte_trouvee());
        if (!q2.getQuad_valid()){
            txt_inst_temp=QString::fromStdString("Ton second Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
            ui->Instruction_label->setText(txt_inst_temp);
        } else {

            QString txt_temp=QString::fromStdString(q2.toString());
            if(etatJeu==1){
                ui->J1_quad2_label->setText(txt_temp);
                J1->addQuad2(q);
                cout<<"--- J1 quad 2 ---"<<endl;
            } else if (etatJeu==2){
                ui->J2_quad2_label->setText(txt_temp);
                J2->addQuad2(q);
                cout<<"--- J2 quad 2 ---"<<endl;
            }
            if (etatJeu==1) {
                etatJeu=2;
            } else if (etatJeu==2){
                etatJeu=1;
            }
            txt_inst_temp=QString::fromStdString("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton premier Quadrimon");
            txt_button_temp=QString::fromStdString("Enregistrer le premier Quadrimon de Joueur "+to_string(getEtatJeu()));
            ui->Instruction_label->setText(txt_inst_temp);
            ui->capture_button->setText(txt_button_temp);
            phaseIni+=1;

        }
    } else if (phaseIni==3){
        cout<<"--- PHASE INI 3 ATTEINT ---"<<endl;
        quadrimon q3 = quadrimon(Get_Carte_trouvee());
        if (!q3.getQuad_valid()){
            txt_inst_temp=QString::fromStdString("Ton premier Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
            ui->Instruction_label->setText(txt_inst_temp);
        } else {
            QString txt_temp=QString::fromStdString(q3.toString());
            cout<<"--- PHASE INI 3.1 ATTEINT ---"<<endl;
            if(etatJeu==1){
                ui->J1_quad1_label->setText(txt_temp);
                cout<<"--- J1 quad 1 ---"<< J1->q1add<<endl;
                J1->addQuad1(q);

            } else if (etatJeu==2){
                ui->J2_quad1_label->setText(txt_temp);
                cout<<"--- J2 quad 1 ---"<< J1->q1add<<endl;
                J2->addQuad1(q);

            }
            cout<<"--- PHASE INI 3.2 ATTEINT ---"<<endl;
            txt_inst_temp=QString::fromStdString("Joueur "+to_string(getEtatJeu())+", tu dois enregistrer ton second Quadrimon");
            txt_button_temp=QString::fromStdString("Enregistrer le second Quadrimon de Joueur "+to_string(getEtatJeu()));
            ui->Instruction_label->setText(txt_inst_temp);
            ui->capture_button->setText(txt_button_temp);
            phaseIni+=1;
            cout<<"--- PHASE INI 3.3 ATTEINT ---"<<endl;
        }
    } else if (phaseIni==4) {
        cout<<"--- PHASE INI 4 ATTEINT ---"<<endl;
        quadrimon q4 = quadrimon(Get_Carte_trouvee());
        if (!q4.getQuad_valid()){
            txt_inst_temp=QString::fromStdString("Ton second Quadrimon n'a été reconnu, \n Joueur "+to_string(getEtatJeu())+" recommence !");
            ui->Instruction_label->setText(txt_inst_temp);
        } else {
            QString txt_temp=QString::fromStdString(q4.toString());
            if(etatJeu==1){
                cout<<"--- PHASE INI 4.1 ATTEINT ---"<<endl;
                ui->J1_quad2_label->setText(txt_temp);
                J1->addQuad2(q);
                cout<<"--- J1 quad 2 ---"<<endl;
            } else if (etatJeu==2){
                cout<<"--- PHASE INI 4.1 ATTEINT ---"<<endl;
                ui->J2_quad2_label->setText(txt_temp);
                J2->addQuad2(q);
                cout<<"--- J2 quad 2 ---"<<endl;
            }
            phaseIni+=1;
            if (etatJeu==1) {
                etatJeu=2;
            } else if (etatJeu==2){
                etatJeu=1;
            }
            txt_inst_temp=QString::fromStdString(" FIN POUR L'INSTANT");
            txt_button_temp=QString::fromStdString("Enregistrer Quadrimon"+to_string(getEtatJeu()));
            ui->Instruction_label->setText(txt_inst_temp);
            ui->capture_button->setText(txt_button_temp);
        }
    }
}
