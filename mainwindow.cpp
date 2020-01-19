#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}


int MainWindow::lancer(Personne * utilisateur)
{
    if(typeid (*utilisateur) == typeid (Gestionnaire))
    {
        GestWidget * gestWidget= new GestWidget(this);
        ui->centralWidget=gestWidget;
        return 1;

    }


    else if(typeid (*utilisateur) == typeid (Enseignant))
    {
       enseignantWidget * ensWidget= new enseignantWidget(this);
        ui->centralWidget=ensWidget;
        return 1;
    }

    else if(typeid (*utilisateur) == typeid (Eleve))
    {
       elevWidget * elvWidget= new elevWidget(this);
        ui->centralWidget=elvWidget;
        return 1;

    }


    else
    {

        return 0;
    }
}

