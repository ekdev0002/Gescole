#include "commtform.h"
#include "ui_commtform.h"

#include <iostream>
CommtForm::CommtForm(QString _idCandidature,QTreeWidgetItem *_treeComt,std::vector <Commentaire*> * _listCom,QWidget *parent) :
    QWidget(parent),idCandidature(_idCandidature),
    treeComt( _treeComt), listCom (_listCom),
    ui(new Ui::CommtForm)
{
    ui->setupUi(this);
    connect(ui->ValiderBouton, SIGNAL(clicked()), this, SLOT(valider()));
}

CommtForm::~CommtForm()
{
    delete ui;
}

void CommtForm::valider()
{
 QString text=ui->textEdit->toPlainText();

 QString id="COMT-"+Service::genererId();
 QString date=QDateTime::currentDateTime().toString();

 Commentaire * newCom = new Commentaire(id,text,date,Service::GetutilisateurCourant()->Getid(),idCandidature);
 listCom->push_back(newCom);


 treeComt->setText(0, QVariant(listCom->size()).toString());
 treeComt->setText(1, text);
 this->close();
}
