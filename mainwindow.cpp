#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reco_carte.h"

#include <random>
#include <iostream>

// Initialisation du générateur de nombres aléatoires avec une graine
std::random_device rd;
std::mt19937 generator(rd()); // Utilisation du générateur Mersenne Twister 19937

// Définition des bornes
int borneMin = 1;
int borneMax = 100;

// Définition de la distribution uniforme
std::uniform_int_distribution<int> distribution(borneMin, borneMax);

// Génération d'un nombre aléatoire entre borneMin et borneMax
int nombreAleatoire = distribution(generator);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_capture_button_clicked()
{
    Reco_carte *w = new Reco_carte(this);
    w->exec();
    next_turn();
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
