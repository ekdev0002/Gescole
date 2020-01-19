#include "saisirnoteform.h"
#include "ui_saisirnoteform.h"
#include <iostream>
#include "mythread.h"

SaisirNoteForm::SaisirNoteForm(QString _idMatiere,QWidget *parent) :
    QWidget(parent),idMatiere(_idMatiere),
    ui(new Ui::SaisirNoteForm)
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(ui->formLayoutWidget);
    QString idClasse;



    for(int i=0;i<Service::GetlistMatiere().size();i++)
    {
        if(Service::GetlistMatiere()[i]->Getid()==idMatiere)
        {
            idClasse=Service::GetlistMatiere()[i]->GetidClasse();
            ui->matiere->setText("Matiere: "+Service::GetlistMatiere()[i]->Getlibelle());
            coef=Service::GetlistMatiere()[i]->Getcoef();
            ui->coefficient->setText("Coefficient: "+QVariant(coef).toString());
        }
    }

    for(int i=0;i<Service::GetlistElev().size();i++)
    {
        if(Service::GetlistElev()[i]->GetidClasse()==idClasse)
        {
            QLabel * lab=new QLabel();
            QDoubleSpinBox * edit= new QDoubleSpinBox();
            lab->setText(Service::GetlistElev()[i]->Getnom()+" "+ Service::GetlistElev()[i]->Getprenom());
            ui->formLayout->addRow(lab,edit);
            listSpin.push_back(edit);
            listEleve.push_back(Service::GetlistElev()[i]);
        }
    }

    connect(ui->valider, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->annuler, SIGNAL(clicked()), this, SLOT(valider()));
}

SaisirNoteForm::~SaisirNoteForm()
{
    delete ui;
}

void SaisirNoteForm::valider()
{
    this->close();
    std::vector <Note*> listNote;
    for (int i=0;i<listSpin.size();i++)
    {
        Note * newNote= new Note();
        newNote->SetidMatiere(idMatiere);
        newNote->Setnote(listSpin[i]->value());
        newNote->Setcoef(coef);
        newNote->SetidEleve(listEleve[i]->Getid());
        newNote->Setintitule(ui->intitule->text());
        listNote.push_back(newNote);
    }

    MyThread * newThread=new MyThread();
    newThread->run(listNote);
}

void SaisirNoteForm::annuler()
{

}
