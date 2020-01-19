#include "creereleve.h"
#include "ui_creereleve.h"
#include <QMessageBox>

CreerEleve::CreerEleve(QTreeWidgetItem * _treeItem,QTreeWidgetItem * _treeItemCand,QTreeWidgetItem * _treeItemClasse,QWidget *parent) :
    QWidget(parent),treeItem(_treeItem),treeItemClasse (_treeItemClasse),treeItemCand (_treeItemCand),
    ui(new Ui::CreerEleve)
{
    ui->setupUi(this);



    for(int i=0;i<Service::GetlistCandt().size();i++)
    {
        ui->candidat->addItem(Service::GetlistCandt()[i]->Getnom()+" "+Service::GetlistCandt()[i]->Getprenom());
    }

    for(int i=0;i<Service::GetlistClass().size();i++)
    {
        ui->classe->addItem(Service::GetlistClass()[i]->Getlibelle());
    }

    for(int i=0;i<Service::GetlistEns().size();i++)
    {
        ui->enseignant->addItem(Service::GetlistEns()[i]->Getnom()+" "+Service::GetlistEns()[i]->Getprenom());
    }



    connect(ui->valider, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->annuler, SIGNAL(clicked()), this, SLOT(annuler()));
    connect(ui->candidat, SIGNAL(currentIndexChanged(int)), this, SLOT(change(int)));


    change(1);

}

CreerEleve::~CreerEleve()
{
    delete ui;
}
void CreerEleve::valider()
{
    QTreeWidgetItem * ptreeItem=new QTreeWidgetItem();


    Eleve * newElev= new Eleve();
    newElev->Setid(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getid());
    newElev->Setnom(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getnom());
    newElev->Setprenom(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getprenom());
    newElev->Setage(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getage());
    newElev->Setsexe(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getsexe());
    newElev->Setcontact(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getcontact());
    newElev->Setlogin(ui->login->text());
    newElev->Setpassword(ui->password->text());
    newElev->SetidClasse(Service::GetlistCandidature()[ui->candidat->currentIndex()]->GetidClasse());

    Service::Persister(newElev);

    ptreeItem->setText(0,newElev->Getnom());
    ptreeItem->setText(1, newElev->Getprenom());
    treeItem->addChild(ptreeItem);
    treeItem->setText(0,"Eleves");
    treeItem->setText(1,QVariant(Service::GetlistElev().size()).toString());

    for (int i=0;i<Service::GetlistClass().size();i++)
    {
        if(Service::GetlistClass()[i]->Getid()==newElev->GetidClasse())
        {
            treeItemClasse->child(i)->setText(1,QVariant(Service::GetlistClass()[i]->Geteffectif()).toString());
        }
    }


    for (int i=0;i<Service::GetlistCandidature().size();i++)
    {
        if(Service::GetlistCandidature()[i]->Getid()==newElev->Getid())
        {
            treeItemCand->takeChild(i);
        }
    }



    this->close();

}
void CreerEleve::annuler()
{
    this->close();
}
void CreerEleve::change(int a)
{
    if(Service::GetlistCandidature()[ui->candidat->currentIndex()]->GetstatutAccepte()=="Accepte"  && Service::GetlistCandidature()[ui->candidat->currentIndex()]->GetstatutClose()=="Close")
    {
        ui->age->setValue(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getage());
        for(int i=0;i<Service::GetlistClass().size();i++)
        {
            if(Service::GetlistClass()[i]->Getid() == Service::GetlistCandidature()[ui->candidat->currentIndex()]->GetidClasse() )
            {
                ui->classe->setCurrentIndex(i);
            }
        }

        for(int i=0;i<Service::GetlistEns().size();i++)
        {
            if(Service::GetlistEns()[i]->Getid() == Service::GetlistCandidature()[ui->candidat->currentIndex()]->GetidProfesseur() )
            {
                ui->enseignant->setCurrentIndex(i);
            }
        }


        ui->contact->setText(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getcontact());
        ui->nom->setText(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getnom());
        ui->prenom->setText(Service::GetlistCandt()[ui->candidat->currentIndex()]->Getprenom());
    }
    else {

        QMessageBox::warning(this, "Erreur", " Statut de candidataure à:"+Service::GetlistCandidature()[ui->candidat->currentIndex()]->GetstatutAccepte()+" et "+Service::GetlistCandidature()[ui->candidat->currentIndex()]->GetstatutClose());
        ui->age->setValue(0);
        ui->classe->setCurrentText("");
        ui->enseignant->setCurrentText("");
        ui->contact->setText("");
        ui->nom->setText("");
        ui->prenom->setText("");

    }
}
