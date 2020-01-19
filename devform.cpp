#include "devform.h"
#include "ui_devform.h"

DevForm::DevForm(QCalendarWidget * _calWidget,QWidget *parent) :
    QWidget(parent),calWidget(_calWidget),
    ui(new Ui::DevForm)
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

DevForm::~DevForm()
{
    delete ui;
}
void DevForm::annuler()
{
 this->close();
}

void DevForm::valider()
{
    Devoir * newDev = new Devoir();
    QString id="DEVR-";
    id=id+Service::genererId();
    newDev->Setid(id);
    newDev->Setduree(ui->nombreHeure->value());
    newDev->SetidMatiere(Service::GetlistMatiere()[ui->classe_matiere->currentIndex()]->Getid());
    newDev->SetdateHeure(ui->dateDebut->dateTime());
    Service::Persister(newDev);
    QTextCharFormat colorDate;
    colorDate.setBackground(Qt::yellow);
    calWidget->setDateTextFormat(newDev->GetdateHeure().date(),colorDate);

    this->close();

}
