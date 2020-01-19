#include "gestwidget.h"
#include "ui_gestwidget.h"

GestWidget::GestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GestWidget)
{
    ui->setupUi(this);

    //Affichages des donnee d'accueil
    QStringList val={"Nom","Effectif"};
    ui->treeWidget->setHeaderLabels(val);
    ui->treeWidget->setColumnCount(2);
    QPixmap * pic = new QPixmap(":/new/prefix1/images/graduade.png");
    QPixmap * pic2 = new QPixmap(":/new/prefix1/images/7.jpg");

    ui->image->setPixmap(*pic);


    listRoot.push_back(addTreeRoot("Enseignants",QVariant(Service::GetlistEns().size()).toString()));
    for(int i=0;i<Service::GetlistEns().size();i++)
    {
        addTreeChild(0,Service::GetlistEns()[i]->Getnom(),Service::GetlistEns()[i]->Getprenom());
    }

    listRoot.push_back(addTreeRoot("Eleves",QVariant(Service::GetlistElev().size()).toString()));
    for(int i=0;i<Service::GetlistElev().size();i++)
    {
        addTreeChild(1,Service::GetlistElev()[i]->Getnom(),Service::GetlistElev()[i]->Getprenom());
    }

    listRoot.push_back(addTreeRoot("Candidatures",QVariant(Service::GetlistCandidature().size()).toString()));
    for(int i=0;i<Service::GetlistCandidature().size();i++)
    {
        addTreeChild(2,Service::GetlistCandt()[i]->Getnom()+" "+ Service::GetlistCandt()[i]->Getprenom(),Service::GetlistCandidature()[i]->GetstatutAccepte()+" \("+Service::GetlistCandidature()[i]->GetstatutClose()+"\) ");
    }

    listRoot.push_back(addTreeRoot("Matière",QVariant(Service::GetlistMatiere().size()).toString()));
    for(int i=0;i<Service::GetlistMatiere().size();i++)
    {
        addTreeChild(3,Service::GetlistMatiere()[i]->Getlibelle()," ");
    }


    listRoot.push_back(addTreeRoot("Classes",QVariant(Service::GetlistClass().size()).toString()));
    for(int i=0;i<Service::GetlistClass().size();i++)
    {
        addTreeChild(4,Service::GetlistClass()[i]->Getlibelle(),QVariant(Service::GetlistClass()[i]->Geteffectif()).toString());
    }


    connect(ui->ajouterBouton, SIGNAL(clicked()), this, SLOT(ajouter()));
    connect(ui->modifierBouton, SIGNAL(clicked()), this, SLOT(modifier()));
    QPalette palette;
    QBrush brush(*pic2);
    palette.setBrush(QPalette::Window,brush);
    ui->label_2->setPixmap(*pic2);

}

GestWidget::~GestWidget()
{
    delete ui;
    Service::closeDB();
    Service::Nettoyage();
}

QTreeWidgetItem* GestWidget::addTreeRoot(QString name, QString description)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    return  treeItem;
}

void GestWidget::addTreeChild(int idParent,QString name, QString description)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setText(1, description);
   listRoot[idParent]->addChild(treeItem);
}

void GestWidget::ajouter()
{
    if(listRoot[0]->isSelected())
    {
        EnseignantForm * ensForm=new EnseignantForm(listRoot[0],0);
        ensForm->show();
    }

    else if(listRoot[1]->isSelected())
    {
        CreerEleve * elevForm=new CreerEleve(listRoot[1],listRoot[2],listRoot[4],0);
        elevForm->show();

    }

    else if(listRoot[2]->isSelected())
    {
        QString idcandt;
        idcandt+="CADT-"+Service::genererId();
        CandidatureForm * candForm=new CandidatureForm(idcandt,listRoot[2],0);
        candForm->show();
    }

    else if(listRoot[3]->isSelected())
    {
        CreerMatiere * matForm=new CreerMatiere(listRoot[3],0);
        matForm->show();
    }

    else if(listRoot[4]->isSelected())
    {
        CreerClasse * clasForm=new CreerClasse(listRoot[4],0);
        clasForm->show();
    }
}

void GestWidget::modifier()
{
    for(int i=0;i<listRoot[2]->childCount();i++)
    {
        if(listRoot[2]->child(i)->isSelected())
        {
            CandidatureForm * candForm=new CandidatureForm(i,listRoot[2],0);
            candForm->show();

        }
    }
}
