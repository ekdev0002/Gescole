#include "coursform.h"
#include "ui_coursform.h"

CoursForm::CoursForm(QCalendarWidget * _calWidget,QWidget *parent) :
    QWidget(parent),calWidget(_calWidget),
    ui(new Ui::CoursForm)
{
    ui->setupUi(this);
    for(int i=0;i<Service::GetlistMatiere().size();i++)
    {
        for(int j=0;j<Service::GetlistClass().size();j++)
        {
            if( (Service::GetlistMatiere()[i]->GetidClasse()==Service::GetlistClass()[j]->Getid()))
            {
                ui->classe_matiere->addItem(Service::GetlistClass()[j]->Getlibelle()+"\\"+Service::GetlistMatiere()[i]->Getlibelle());
            }
        }
    }

    ui->dateDebut->setDateTime(QDateTime::currentDateTime());
    connect(ui->valider, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->annuler, SIGNAL(clicked()), this, SLOT(annuler()));

}

CoursForm::~CoursForm()
{
    delete ui;
}
void CoursForm::annuler()
{
 this->close();
}

void CoursForm::valider()
{
    Cours * newCours = new Cours();
    QString id="COUR-";
    id=id+Service::genererId();
    newCours->Setid(id);
    newCours->Setduree(ui->nombreHeure->value());
    newCours->SetidMatiere(Service::GetlistMatiere()[ui->classe_matiere->currentIndex()]->Getid());
    newCours->SetDateHeure(ui->dateDebut->dateTime());
    Service::Persister(newCours);
    QTextCharFormat colorDate;
    colorDate.setBackground(Qt::green);
    calWidget->setDateTextFormat(newCours->GetDateHeure().date(),colorDate);

    this->close();

}
