#include "creermatiere.h"
#include "ui_creermatiere.h"

CreerMatiere::CreerMatiere(QTreeWidgetItem * _treeItem,QWidget *parent) :
    QWidget(parent),treeItem(_treeItem),
    ui(new Ui::CreerMatiere)
{
    ui->setupUi(this);

    for(int i=0;i<Service::GetlistClass().size();i++)
    {
     ui->comboClasse->addItem(Service::GetlistClass()[i]->Getlibelle());
    }
    for(int i=0;i<Service::GetlistEns().size();i++)
    {
     ui->comboProf->addItem(Service::GetlistEns()[i]->Getnom()+" "+Service::GetlistEns()[i]->Getprenom());
    }

    connect(ui->valider, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->annuler, SIGNAL(clicked()), this, SLOT(annuler()));
}

CreerMatiere::~CreerMatiere()
{
    delete ui;
}
void CreerMatiere::valider()
{
    QString id="MATR-";
    id+=Service::genererId();
    QTreeWidgetItem * ptreeItem=new QTreeWidgetItem();

    Matiere * newMat = new Matiere();
    newMat->Setid(id);
    newMat->Setlibelle(ui->intitule->text());
    newMat->SetidClasse(Service::GetlistClass()[ui->comboClasse->currentIndex()]->Getid());
    newMat->SetidProfesseur(Service::GetlistEns()[ui->comboProf->currentIndex()]->Getid());
    newMat->Setcoef(ui->age->value());

    Service::Persister(newMat);

    ptreeItem->setText(0, newMat->Getlibelle() );
    ptreeItem->setText(1, " ");
    treeItem->addChild(ptreeItem);
    treeItem->setText(0,"Matiere");
    treeItem->setText(1,QVariant(Service::GetlistMatiere().size()).toString());


    this->close();
}
void CreerMatiere::annuler()
{
    this->close();
}


