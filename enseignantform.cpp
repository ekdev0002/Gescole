#include "enseignantform.h"
#include "ui_enseignantform.h"

EnseignantForm::EnseignantForm(QTreeWidgetItem * _treeItem, QWidget *parent) :
    QWidget(parent),treeItem(_treeItem),
    ui(new Ui::EnseignantForm)
{
    ui->setupUi(this);


    connect(ui->validerBouton, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->annulerBouton, SIGNAL(clicked()), this, SLOT(annuler()));

}

EnseignantForm::~EnseignantForm()
{
    delete ui;
}

void EnseignantForm::valider()
{
    QString id="ENS-"+Service::genererId();
    QTreeWidgetItem *ptreeItem = new QTreeWidgetItem();

    Enseignant * newEns = new Enseignant(id,ui->nomEdit->text(),ui->prenomEdit->text(),ui->spinAge->value(),ui->sexeBox->currentText(),ui->loginEdit->text(),ui->pwdEdit->text(),ui->contactEdit->text());



    Service::Persister(newEns);

    ptreeItem->setText(0,newEns->Getnom());
    ptreeItem->setText(1, newEns->Getprenom());
    treeItem->addChild(ptreeItem);
    treeItem->setText(0,"Enseignant");
    treeItem->setText(1,QVariant(Service::GetlistEns().size()).toString());
    this->close();
}

void EnseignantForm::annuler()
{
    this->close();
}
