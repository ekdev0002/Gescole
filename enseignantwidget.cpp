/* *******************Fenêtre principale du gestionnaire**********************************
    void addTreeRoot(QString name, QString description): fonction d'ajout d'item principale
    void addTreeChild(int idParent,QString name, QString description): fonction d'ajout d'item secondaire
    void modifier(); fonction excetutee lorsque l'enseignant veu modifier une candidature
    void plannifierCours(); fonction excecutee lorsque l'enseignant veut plannifier un cours
    void plannifierDev(); fonction excecutee lorsque l'enseignant veut plannifier un devoir
    void info(); fonction excecutee lorsque l'enseignant clique sur une case coloriee pour avoir des info sur l'activite en question
    void saisir(); fonction excecutee lorsque l'enseignant saisi les notes
*/



#include "enseignantwidget.h"
#include "ui_enseignantwidget.h"
#include <QTextCharFormat>

enseignantWidget::enseignantWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enseignantWidget)
{
    ui->setupUi(this);

    ui->enseignant->setText(Service::GetutilisateurCourant()->Getnom()+" "+Service::GetutilisateurCourant()->Getprenom());
    QPixmap * pic = new QPixmap(":/new/prefix1/images/jaune.png");
    ui->jaune->setPixmap(*pic);
    QPixmap * pic1 = new QPixmap(":/new/prefix1/images/vert.png");
    ui->vert->setPixmap(*pic1);

    //Affichages des donnee d'accueil
    QStringList val={"Intitulé"," "};
    ui->treeWidget->setHeaderLabels(val);
    ui->treeWidget->setColumnCount(2);
    planning=new Planning();


    //ajout des itemes

    listRoot.push_back(addTreeRoot("Candidatures affiliées",QVariant(Service::GetlistCandidature().size()).toString()));
    for(int i=0;i<Service::GetlistCandidature().size();i++)
    {

        for(int j=0;j<Service::GetlistCandt().size();j++)
        {
            if( (Service::GetlistCandt()[j]->Getid()==Service::GetlistCandidature()[i]->Getid()) && (Service::GetutilisateurCourant()->Getid()==Service::GetlistCandidature()[i]->GetidProfesseur()))
            {
                addTreeChild(0,Service::GetlistCandt()[j]->Getnom()+" "+ Service::GetlistCandt()[j]->Getprenom(),Service::GetlistCandidature()[i]->GetstatutAccepte()+"\("+Service::GetlistCandidature()[i]->GetstatutClose()+"\)");
            }
        }
    }

    listRoot.push_back(addTreeRoot("Classes affiliées",QVariant(Service::GetlistMatiere().size()).toString()));
    for(int i=0;i<Service::GetlistMatiere().size();i++)
    {
        for(int j=0;j<Service::GetlistClass().size();j++)
        {
            if( (Service::GetlistMatiere()[i]->GetidClasse()==Service::GetlistClass()[j]->Getid()))
            {
                addTreeChild(1,Service::GetlistClass()[j]->Getlibelle(),Service::GetlistMatiere()[i]->Getlibelle());
                listIdMatiere.push_back(Service::GetlistMatiere()[i]->Getid());
            }
        }


        for(int j=0;j<Service::GetlistCours().size();j++)
        {
            if( (Service::GetlistMatiere()[i]->Getid()==Service::GetlistCours()[j]->GetidMatiere()))
            {
                QTextCharFormat colorDate;
                colorDate.setBackground(Qt::green);
                ui->calendarWidget->setDateTextFormat(Service::GetlistCours()[j]->GetDateHeure().date(),colorDate);
                planning->addCours(Service::GetlistCours()[j]);
            }
        }


        for(int j=0;j<Service::GetlistDevoir().size();j++)
        {
            if( (Service::GetlistMatiere()[i]->Getid()==Service::GetlistDevoir()[j]->GetidMatiere()))
            {
                QTextCharFormat colorDate;
                colorDate.setBackground(Qt::yellow);
                ui->calendarWidget->setDateTextFormat(Service::GetlistDevoir()[j]->GetdateHeure().date(),colorDate);
                planning->addDevoir(Service::GetlistDevoir()[j]);
            }
        }


    }



   connect(ui->modifierBouton, SIGNAL(clicked()), this, SLOT(modifier()));
   connect(ui->plannifierCours, SIGNAL(clicked()), this, SLOT(plannifierCours()));
   connect(ui->plannifierDev, SIGNAL(clicked()), this, SLOT(plannifierDev()));
   connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(info()));
   connect(ui->saisirNote, SIGNAL(clicked()), this, SLOT(saisir()));


}

void enseignantWidget::plannifierCours()
{
    CoursForm * nouvCours= new CoursForm(ui->calendarWidget);
    nouvCours->show();

}
void enseignantWidget::plannifierDev()
{
    DevForm * nouvDev=new DevForm(ui->calendarWidget);
    nouvDev->show();
}

void enseignantWidget::modifier()
{
    for(int i=0;i<listRoot[0]->childCount();i++)
    {
        if(listRoot[0]->child(i)->isSelected())
        {
            CandidatureForm * candForm=new CandidatureForm(i,0,listRoot[0],0);
            candForm->show();
        }
    }
}

void enseignantWidget::saisir()
{
    for (int i=0;i<listRoot[1]->childCount();i++)
    {
        if(listRoot[1]->child(i)->isSelected())
        {
            SaisirNoteForm * newSaisi= new SaisirNoteForm(listIdMatiere[i]);
            newSaisi->show();
        }
    }
}



QTreeWidgetItem* enseignantWidget::addTreeRoot(QString name, QString description)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    return  treeItem;
}

void enseignantWidget::addTreeChild(int idParent,QString name, QString description)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setText(1, description);
   listRoot[idParent]->addChild(treeItem);
}

enseignantWidget::~enseignantWidget()
{
    delete ui;
}

void enseignantWidget::info()
{
    for(int i=0;i<planning->GetlisteCours().size();i++)
    {
        if(planning->GetlisteCours()[i]->GetDateHeure().date()==ui->calendarWidget->selectedDate())
        {
            for (int j=0;j<Service::GetlistMatiere().size();j++)
            {
                if(Service::GetlistMatiere()[j]->Getid()==planning->GetlisteCours()[i]->GetidMatiere())
                   QMessageBox::information(this, "Cours", "Cours de: " +Service::GetlistMatiere()[j]->Getlibelle()+ ", Duree: " + QVariant(planning->GetlisteCours()[i]->Getduree()).toString()+ " heures," + " à partir de "+planning->GetlisteCours()[i]->GetDateHeure().time().toString());
            }
        }
    }
    for(int i=0;i<planning->GetlisteDevoirs().size();i++)
    {
        if(planning->GetlisteDevoirs()[i]->GetdateHeure().date()==ui->calendarWidget->selectedDate())
        {
            for (int j=0;j<Service::GetlistMatiere().size();j++)
            {
                if(Service::GetlistMatiere()[j]->Getid()==planning->GetlisteDevoirs()[i]->GetidMatiere())
                   QMessageBox::information(this, "Devoir", "Devoir de: " +Service::GetlistMatiere()[j]->Getlibelle()+ ", Duree:" + QVariant(planning->GetlisteDevoirs()[i]->Getduree()).toString()+ " heures," + " à partir de "+planning->GetlisteDevoirs()[i]->GetdateHeure().time().toString());
            }

        }
    }
}
