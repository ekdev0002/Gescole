#include "candidatureform.h"
#include "ui_candidatureform.h"


//constructeur lancé à la creation d'une candidature
CandidatureForm::CandidatureForm(QString _idCandidature,QTreeWidgetItem *_treeItem,QWidget *parent) :
    QWidget(parent),
    idCandidature (_idCandidature),treeItem (_treeItem),
    ui(new Ui::CandidatureForm)
{
    ui->setupUi(this);

    connect(ui->ajouterBoutonFichier, SIGNAL(clicked()), this, SLOT(submitFile()));
    connect(ui->ajouterComment, SIGNAL(clicked()), this, SLOT(addComment()));
    connect(ui->ValiderBouton, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->quitter, SIGNAL(clicked()), this, SLOT(quitter()));
    connect(ui->checkClose, SIGNAL(stateChanged(int)), this, SLOT(changerStatutclose(int)));
    connect(ui->checkAccept, SIGNAL(stateChanged(int)), this, SLOT(changerStatutaccept(int)));
    connect(ui->checkRefuse, SIGNAL(stateChanged(int)), this, SLOT(changerStatutrefus(int)));

    QStringList val={"N","Nom"};
    ui->treeDoc->setHeaderLabels(val);
    ui->treeDoc->setColumnCount(2);

    for(int i=0;i<Service::GetlistClass().size();i++)
    {
     ui->classe->addItem(Service::GetlistClass()[i]->Getlibelle());
    }
    for(int i=0;i<Service::GetlistEns().size();i++)
    {
     ui->enseignant->addItem(Service::GetlistEns()[i]->Getnom()+" "+Service::GetlistEns()[i]->Getprenom());
    }
}


//constructeur lancé à la modification d'une candidature
CandidatureForm::CandidatureForm(int _i,QTreeWidgetItem *_treeItem,QWidget *parent) :
    QWidget(parent),
    indice (_i),treeItem (_treeItem),
    ui(new Ui::CandidatureForm)
{
    ui->setupUi(this);
    idCandidature=Service::GetlistCandidature()[indice]->Getid();

    connect(ui->ajouterBoutonFichier, SIGNAL(clicked()), this, SLOT(submitFile()));
    connect(ui->ajouterComment, SIGNAL(clicked()), this, SLOT(addComment()));
    connect(ui->ValiderBouton, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->quitter, SIGNAL(clicked()), this, SLOT(quitter()));
    connect(ui->checkClose, SIGNAL(stateChanged(int)), this, SLOT(changerStatutclose(int)));
    connect(ui->checkAccept, SIGNAL(stateChanged(int)), this, SLOT(changerStatutaccept(int)));
    connect(ui->checkRefuse, SIGNAL(stateChanged(int)), this, SLOT(changerStatutrefus(int)));

    QStringList val={"N","Nom"};
    ui->treeDoc->setHeaderLabels(val);
    ui->treeDoc->setColumnCount(2);

    for(int i=0;i<Service::GetlistCandidature()[indice]->GetlisteDocument().size();i++)
    {
        QTreeWidgetItem *ptreeItem = new QTreeWidgetItem(ui->treeDoc);
        ptreeItem->setText(0, QVariant(i+1).toString() );
        ptreeItem->setText(1,Service::GetlistCandidature()[indice]->GetlisteDocument()[i]->Getlibelle());
        listDocWidget.push_back(ptreeItem);
    }

    QStringList val2={"N","Commentaire"};
    ui->treeCmt->setHeaderLabels(val2);
    ui->treeCmt->setColumnCount(2);
    for(int i=0;i<Service::GetlistCandidature()[indice]->Getcommentaires().size();i++)
    {
        QTreeWidgetItem *ptreeItem = new QTreeWidgetItem(ui->treeCmt);
        ptreeItem->setText(0, QVariant(i+1).toString() );
        ptreeItem->setText(1,Service::GetlistCandidature()[indice]->Getcommentaires()[i]->Gettext());
    }


    ui->age->setValue(Service::GetlistCandt()[indice]->Getage());
    if( Service::GetlistCandidature()[indice]->GetstatutAccepte() == "Accepte" ) {
            ui->checkAccept->setChecked(true);
            ui->checkRefuse->setChecked(false);
    }

    else {
            ui->checkAccept->setChecked(false);
            ui->checkRefuse->setChecked(true);
    }

    if( Service::GetlistCandidature()[indice]->GetstatutClose()== "Close" )
    {
        ui->checkAccept->setDisabled(true);
        ui->checkRefuse->setDisabled(true);
    }

    ui->contact->setText(Service::GetlistCandt()[indice]->Getcontact());
    ui->contact->setReadOnly(true);
    ui->nom->setText(Service::GetlistCandt()[indice]->Getnom());
    ui->nom->setReadOnly(true);
    ui->prenom->setText(Service::GetlistCandt()[indice]->Getprenom());
    ui->prenom->setReadOnly(true);
    ui->sexe->setCurrentText(Service::GetlistCandt()[indice]->Getsexe());
    ui->sexe->setEnabled(false);

    for(int i=0;i<Service::GetlistClass().size();i++)
    {
     ui->classe->addItem(Service::GetlistClass()[i]->Getlibelle());
    }
    for(int i=0;i<Service::GetlistEns().size();i++)
    {
     ui->enseignant->addItem(Service::GetlistEns()[i]->Getnom()+" "+Service::GetlistEns()[i]->Getprenom());
    }


    for(int i=0;i<Service::GetlistClass().size();i++)
    {
        if( (Service::GetlistCandidature()[indice]->GetidClasse()) == (Service::GetlistClass()[i]->Getid()) )
        {
            ui->classe->setCurrentIndex(i);
        }

    }
    for(int i=0;i<Service::GetlistEns().size();i++)
    {
     if( (Service::GetlistCandidature()[indice]->GetidProfesseur()) == (Service::GetlistEns()[i]->Getid()) )
     {
         ui->enseignant->setCurrentIndex(i);
     }
    }

}


//second constructeur lancé à la modification d'une candidature, cette fois par un enseignant. le paramètre _j sert juste à differencier ce constructeur et l'autre ci-dessus
CandidatureForm::CandidatureForm(int _i,int _j,QTreeWidgetItem *_treeItem,QWidget *parent) :
    QWidget(parent),
    indice (_i),treeItem (_treeItem),
    ui(new Ui::CandidatureForm)
{
    ui->setupUi(this);

    idCandidature=Service::GetlistCandidature()[indice]->Getid();

    ui->checkClose->setCheckable(false);

    connect(ui->ajouterBoutonFichier, SIGNAL(clicked()), this, SLOT(submitFile()));
    connect(ui->telechargerBouton, SIGNAL(clicked()), this, SLOT(telecharger()));
    connect(ui->ajouterComment, SIGNAL(clicked()), this, SLOT(addComment()));
    connect(ui->ValiderBouton, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->quitter, SIGNAL(clicked()), this, SLOT(quitter()));
    connect(ui->checkClose, SIGNAL(stateChanged(int)), this, SLOT(changerStatutclose(int)));
    connect(ui->checkAccept, SIGNAL(stateChanged(int)), this, SLOT(changerStatutaccept(int)));
    connect(ui->checkRefuse, SIGNAL(stateChanged(int)), this, SLOT(changerStatutrefus(int)));

    QStringList val={"N","Nom"};
    ui->treeDoc->setHeaderLabels(val);
    ui->treeDoc->setColumnCount(2);

    for(int i=0;i<Service::GetlistCandidature()[indice]->GetlisteDocument().size();i++)
    {
        QTreeWidgetItem *ptreeItem = new QTreeWidgetItem(ui->treeDoc);
        ptreeItem->setText(0, QVariant(i+1).toString() );
        ptreeItem->setText(1,Service::GetlistCandidature()[indice]->GetlisteDocument()[i]->Getlibelle());
        listDocWidget.push_back(ptreeItem);
    }

    QStringList val2={"N","Commentaire"};
    ui->treeCmt->setHeaderLabels(val2);
    ui->treeCmt->setColumnCount(2);
    for(int i=0;i<Service::GetlistCandidature()[indice]->Getcommentaires().size();i++)
    {
        QTreeWidgetItem *ptreeItem = new QTreeWidgetItem(ui->treeCmt);
        ptreeItem->setText(0, QVariant(i+1).toString() );
        ptreeItem->setText(1,Service::GetlistCandidature()[indice]->Getcommentaires()[i]->Gettext());
    }


    ui->age->setValue(Service::GetlistCandt()[indice]->Getage());
    if( Service::GetlistCandidature()[indice]->GetstatutAccepte() == "Accepte" ) {
            ui->checkAccept->setChecked(true);
            ui->checkRefuse->setChecked(false);
    }

    else {
            ui->checkAccept->setChecked(false);
            ui->checkRefuse->setChecked(true);
    }

    if( Service::GetlistCandidature()[indice]->GetstatutClose()== "Close" )
    {
        ui->checkAccept->setDisabled(true);
        ui->checkRefuse->setDisabled(true);
    }

    ui->contact->setText(Service::GetlistCandt()[indice]->Getcontact());
    ui->contact->setReadOnly(true);
    ui->nom->setText(Service::GetlistCandt()[indice]->Getnom());
    ui->nom->setReadOnly(true);
    ui->prenom->setText(Service::GetlistCandt()[indice]->Getprenom());
    ui->prenom->setReadOnly(true);
    ui->sexe->setCurrentText(Service::GetlistCandt()[indice]->Getsexe());
    ui->sexe->setEnabled(false);

    for(int i=0;i<Service::GetlistClass().size();i++)
    {
     ui->classe->addItem(Service::GetlistClass()[i]->Getlibelle());
    }
    for(int i=0;i<Service::GetlistEns().size();i++)
    {
     ui->enseignant->addItem(Service::GetlistEns()[i]->Getnom()+" "+Service::GetlistEns()[i]->Getprenom());
    }


    for(int i=0;i<Service::GetlistClass().size();i++)
    {
        if( (Service::GetlistCandidature()[indice]->GetidClasse()) == (Service::GetlistClass()[i]->Getid()) )
        {
            ui->classe->setCurrentIndex(i);
            ui->classe->setEnabled(false);
        }

    }
    for(int i=0;i<Service::GetlistEns().size();i++)
    {
     if( (Service::GetlistCandidature()[indice]->GetidProfesseur()) == (Service::GetlistEns()[i]->Getid()) )
     {
         ui->enseignant->setCurrentIndex(i);
         ui->enseignant->setEnabled(false);
     }
    }

}






CandidatureForm::~CandidatureForm()
{
    delete ui;
}


void CandidatureForm::changerStatutclose(int a)
{
    if(ui->checkClose->isChecked())
    {
        ui->checkAccept->setDisabled(true);
        ui->checkRefuse->setDisabled(true);
    }
    else
    {
        ui->checkAccept->setDisabled(false);
        ui->checkRefuse->setDisabled(false);
    }
}


void CandidatureForm::changerStatutaccept(int a)
{
    if(ui->checkAccept->isChecked())
    {
        ui->checkRefuse->setChecked(false);
    }
    else
    {
        ui->checkRefuse->setChecked(true);
    }
}

void CandidatureForm::changerStatutrefus(int a)
{
    if(ui->checkRefuse->isChecked())
    {
        ui->checkAccept->setChecked(false);
    }
    else
    {
        ui->checkAccept->setChecked(true);
    }
}

void CandidatureForm::submitFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Charger un document de candidature"), QDir::homePath(),
           tr("Document de Candidature (*.pdf *.JPEG *.PNG *.JPG)"));

    if (fileName.isEmpty())
            return;
        else {

            QFile file(fileName);
            QString id=Service::genererId();
            id="DOCM-"+id;
            QFileInfo fileInfo(file.fileName());
            QString filename(fileInfo.fileName());
            if(QFile::copy(fileName,filename))
            {
                QString id="DOCM-";
                id+=Service::genererId();
                Document * newDoc= new Document(id,filename,QDir::currentPath()+"/"+filename,idCandidature);
                listDoc.push_back(newDoc);

                QTreeWidgetItem *ptreeItem = new QTreeWidgetItem(ui->treeDoc);
                ptreeItem->setText(0, QVariant(listDoc.size()).toString() );
                ptreeItem->setText(1, filename);

            }
            else {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
            }
        }
}



void CandidatureForm::telecharger()
{

    for(int i=0;i<listDocWidget.size();i++)
    {
        if(listDocWidget[i]->isSelected())
        {
            QString filename = QFileDialog::getSaveFileName(this,
                   //tr("Enregistrez sous"), /*QDir::homePath()*/" ",
                   tr("Enregistrez sous"),"",
                   tr("Document de Candidature (*.pdf);;(*.PNG);;(*.jpg);;All Files (*)"));

            if (filename.isEmpty())
                    return;
                else {

                    /*QFile file(Service::GetlistCandidature()[indice]->GetlisteDocument()[i]->Geturl());
                    QFileInfo fileInfo(file.fileName());
                    QString filename1(fileInfo.fileName())*/
                    if(QFile::copy(Service::GetlistCandidature()[indice]->GetlisteDocument()[i]->Geturl(),filename))
                    {
                        QMessageBox::information(this, tr("dd"),"well saved");

                    }
                    else
                    {
                        QMessageBox::information(this, tr("Unable to open file"),"bad save");
                    }
                 }
        }
       }
}


void CandidatureForm::valider()
{
    QTreeWidgetItem * ptreeItem=new QTreeWidgetItem();

    Candidat * newCandt=new Candidat(idCandidature,ui->nom->text(),ui->prenom->text(),ui->age->value(),ui->sexe->currentText(),"","",ui->contact->text());
    Candidature * newCand = new Candidature();
    newCand->Setid(idCandidature);
    newCand->SetidClasse(Service::GetlistClass()[ui->classe->currentIndex()]->Getid());
    newCand->SetidProfesseur(Service::GetlistEns()[ui->enseignant->currentIndex()]->Getid());
    newCand->SetlisteDocument(listDoc);
    newCand->Setcommentaires(listCom);
    if(ui->checkAccept->isChecked())
    {
        newCand->SetstatutAccepte("Accepte");
    }
    else {
        newCand->SetstatutAccepte("Refuse");
    }
    if(ui->checkRefuse->isChecked())
    {
        newCand->SetstatutClose("Refuse");
     }
    else {
        newCand->SetstatutAccepte("Accepte");
    }

    if(ui->checkClose->isChecked())
    {
        newCand->SetstatutClose("Close");
    }
    else {
        newCand->SetstatutClose("Open");
    }

    Service::Persister(newCand);
    Service::Persister(newCandt);

    //persistance
    for(int i=0;i<listDoc.size();i++)
    {
        Service::Persister(listDoc[i]);
    }
    for(int i=0;i<listCom.size();i++)
    {
        Service::Persister(listCom[i]);
    }
    bool test=false;
    for(int i=0;i<treeItem->childCount();i++)
    {
        if ( treeItem->child(i)->text(0) == newCandt->Getnom()+" "+newCandt->Getprenom())
        {
           treeItem->child(i)->setText(1,newCand->GetstatutAccepte()+"\("+newCand->GetstatutClose()+"\)");
           test=true;
        }
    }
    if(!test)
    {
        ptreeItem->setText(0,newCandt->Getnom()+" "+newCandt->Getprenom());
        ptreeItem->setText(1, newCand->GetstatutAccepte()+"\("+newCand->GetstatutClose()+"\)");
        treeItem->addChild(ptreeItem);
        //treeItem->setText(0,"Candidature");
        treeItem->setText(1,QVariant(Service::GetlistCandidature().size()).toString());
    }

    this->quitter();
}

void CandidatureForm::quitter()
{
    this->close();
    delete  this;
    for(int i=0;i<listDoc.size();i++)
    {
        delete listDoc[i];
    }
    for(int i=0;i<listCom.size();i++)
    {
        delete listCom[i];
    }
    for(int i=0;i<listDocWidget.size();i++)
    {
        delete listDocWidget[i];
    }

}


void CandidatureForm::addComment()
{
    QStringList val={"N","Commentaire"};
    ui->treeCmt->setHeaderLabels(val);
    ui->treeCmt->setColumnCount(2);


    QTreeWidgetItem *treeCmt = new QTreeWidgetItem(ui->treeCmt);
    CommtForm * cmtform= new CommtForm(idCandidature,treeCmt,&listCom,0);
    cmtform->show();
}
