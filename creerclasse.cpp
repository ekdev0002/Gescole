#include "creerclasse.h"
#include "ui_creerclasse.h"

CreerClasse::CreerClasse(QTreeWidgetItem *_treeItem,QWidget *parent) :
    QWidget(parent),
    treeItem(_treeItem),
    ui(new Ui::CreerClasse)
{
    ui->setupUi(this);

    connect(ui->validerBouton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(ui->annulerBouton, SIGNAL(clicked()), this, SLOT(cancel()));

}

CreerClasse::~CreerClasse()
{
    delete ui;
}
void CreerClasse::submit()
{
    QTreeWidgetItem * ptreeItem = new QTreeWidgetItem();
    QString libelleClasse=ui->lineEdit->text();
    QString id=Service::genererId();
    id="CLAS-" +id;

    Classe * newClasse =new Classe(id,libelleClasse,0);

    Service::Persister(newClasse);

    ptreeItem->setText(0, libelleClasse );
    ptreeItem->setText(1, "0");
    treeItem->addChild(ptreeItem);
    treeItem->setText(0,"Classe");
    treeItem->setText(1,QVariant(Service::GetlistClass().size()).toString());

    this->close();

}

void CreerClasse::cancel()
{
 this->close();
}
