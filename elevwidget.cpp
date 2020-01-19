/* *******************Fenêtre principale de l'eleve**********************************
    void info(); slot pour afficher la fenetre de dialog informant sur le plannif cours et devoir
    void imprimer(); Slot pour imprimer
*/



#include "elevwidget.h"
#include "ui_elevwidget.h"
#include <QPainter>
#include <QTreeWidgetItem>


elevWidget::elevWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::elevWidget)
{
    ui->setupUi(this);

    ui->eleve->setText(Service::GetutilisateurCourant(1)->Getnom()+" "+Service::GetutilisateurCourant(1)->Getprenom());

    for (int i=0;i<Service::GetlistClass().size();i++)
    {
        if(Service::GetutilisateurCourant(1)->GetidClasse()==Service::GetlistClass()[i]->Getid())
         {
            classe=Service::GetlistClass()[i]->Getlibelle();
            effectif=QVariant(Service::GetlistClass()[i]->Geteffectif()).toString();
            ui->classe->setText(classe);
        }
    }

    QPixmap * pic = new QPixmap(":/new/prefix1/images/jaune.png");
    ui->jaune->setPixmap(*pic);
    QPixmap * pic1 = new QPixmap(":/new/prefix1/images/vert.png");
    ui->vert->setPixmap(*pic1);

    //Affichages des donnee d'accueil
    QStringList val={"Epreuve","note/20"};
    ui->treeWidget->setHeaderLabels(val);
    ui->treeWidget->setColumnCount(2);
    planning=new Planning();
    totalNote=0;
    totalNotePond=0;
    totalCoef=0;

    for(int i=0;i<Service::GetlistMatiere().size();i++)
    {

        QTreeWidgetItem * treeItem=new QTreeWidgetItem(ui->treeWidget);
        treeItem->setText(0,Service::GetlistMatiere()[i]->Getlibelle());
        treeItem->setText(1," ");


        //pour le bulletin
        listMatiere.push_back(Service::GetlistMatiere()[i]->Getlibelle());
        float coef=Service::GetlistMatiere()[i]->Getcoef();
        listCoef.push_back(coef);

        totalCoef=totalCoef+coef;


        float note=0;
        for(int k=0;k<Service::GetlistNote().size();k++)
        {
            if( (Service::GetlistNote()[k]->GetidEleve()) == (Service::GetutilisateurCourant(1)->Getid()) && (Service::GetlistNote()[k]->GetidMatiere()==Service::GetlistMatiere()[i]->Getid()))
            {
                QTreeWidgetItem * ptreeItem=new QTreeWidgetItem();
                ptreeItem->setText(0,Service::GetlistNote()[k]->Getintitule());
                ptreeItem->setText(1,QVariant(Service::GetlistNote()[k]->Getnote()).toString());
                treeItem->addChild(ptreeItem);
                note=note+Service::GetlistNote()[k]->Getnote();
            }
        }
        note=note/2;
        listNote.push_back(note);
        totalNote=totalNote+note;

        listNotePond.push_back(coef*note);
        totalNotePond=totalNotePond+(coef*note);

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





    connect(ui->imprimer, SIGNAL(clicked()), this, SLOT(imprimer()));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(info()));

}

elevWidget::~elevWidget()
{
    delete ui;
}
void elevWidget::info()
{
    for(int i=0;i<planning->GetlisteCours().size();i++)
    {
        if(planning->GetlisteCours()[i]->GetDateHeure().date()==ui->calendarWidget->selectedDate())
        {
            for (int j=0;j<Service::GetlistMatiere().size();j++)
            {
                if(Service::GetlistMatiere()[j]->Getid()==planning->GetlisteCours()[i]->GetidMatiere())
                   QMessageBox::information(this, "Cours", "Cours de: " +Service::GetlistMatiere()[j]->Getlibelle()+ ", Duree:" + QVariant(planning->GetlisteCours()[i]->Getduree()).toString()+ " heures," + " à partir de "+planning->GetlisteCours()[i]->GetDateHeure().time().toString());
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

void elevWidget::imprimer()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QString partieNotes="";
    QString decision;
    float moyenne=totalNotePond/(QVariant(totalCoef).toFloat());

    if(moyenne>10)
    {
        decision="Passe en classe superieur";
    }
    else {
        decision="Redouble";
    }

    for(int i=0;i<listNote.size();i++)
    {

        partieNotes=partieNotes+"        <tr>"
        "            <td width='154' valign='top'>"
        "                <p>"
        "                    "+listMatiere[i]+""
        "                </p>"
        "            </td>"
        "            <td width='154' valign='top'>"
        "                <p>"
        "                    "+QVariant(QVariant(listCoef[i]).toInt()).toString()+""
        "                </p>"
        "            </td>"
        "            <td width='154' valign='top'>"
        "                <p>"
        "                    "+QVariant(listNote[i]).toString()+""
        "                </p>"
        "            </td>"
        "            <td width='154' valign='top'>"
        "                <p>"
        "                    "+QVariant(listNotePond[i]).toString()+""
        "                </p>"
        "            </td>"
        "        </tr>";

    }


QString text="<!DOCTYPE html>"
                "<html>"
                "<body>"
                "<p align='center'>"
                "    <strong><u>Groupe Scolaire Saint-Arouna</u></strong>"
                "</p>"
                "<p align='center'>"
                "    <strong><u>Bulletin de note n°: 1555</u></strong>"
                "</p> "
                "<p>"
                "	<strong>Nom : "+Service::GetutilisateurCourant(1)->Getnom()+" </p></strong>"
                "<p>"
                "    <strong>Prénom :"+Service::GetutilisateurCourant(1)->Getprenom()+"</strong>"
                "</p>"
                "<p>"
                "    <strong>Matricule : "+Service::GetutilisateurCourant(1)->Getid()+"</strong>"
                "</p>"
                ""
                "<p>"
                "    <strong>Classe: "+classe+"</strong>"
                "</p>"
                ""
                ""
                "<p>"
                "    <strong>Effectif : "+effectif+"</strong>"
                "</p>"
                ""
                "<table border='1' cellspacing='0' cellpadding='0'>"
                "    <tbody>"
                "        <tr>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    Matière"
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    Coefficient"
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    Moy./20"
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    Moy. Ponderee"
                "                </p>"
                "            </td>"
                "        </tr>"
                +partieNotes+
                "        <tr>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    Total"
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p>"
                +QVariant(totalCoef).toString()+
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p>"
                +QVariant(totalNote).toString()+
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p>"
                +QVariant(totalNotePond).toString()+
                "                </p>"
                "            </td>"
                "        </tr>"
                "    </tbody>"
                "</table>"


                "<table border='1' cellspacing='0' cellpadding='0'>"
                "    <tbody>"
                "        <tr>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    <strong>Moyenne de L’élève</strong>"
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p align='center'>"
                "                    <strong>"+QVariant(moyenne).toString()+"</strong>"
                "                </p>"
                "                <p align='center'>"
                "                    <strong></strong>"
                "                </p>"
                "                <p align='center'>"
                "                    <strong></strong>"
                "                </p>"
                "            </td>"
                "        </tr>"
                "        <tr>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    <strong>Rang de l’élève</strong>"
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p align='center'>"
                "                    <strong> Non Dispo </sup></strong>"
                "                </p>"
                "                <p align='center'>"
                "                    <strong></strong>"
                "                </p>"
                "            </td>"
                "        </tr>"
                "        <tr>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    <strong>decision</strong>"
                "                </p>"
                "            </td>"
                "            <td width='154' valign='top'>"
                "                <p>"
                "                    <strong></strong>"
                "                </p>"
                "                <p>"
                "                    <strong>"+decision+" </strong>"
                "                </p>"
                "                <p>"
                "                    <strong></strong>"
                "                </p>"
                "            </td>"
                "        </tr>"
                "    </tbody>"
                "</table>"
                "<p>"
                "    Poto-Poto le "+QDateTime::currentDateTime().toString()+"                                                                                                     Le Directeur"
                "</p>"
                "<br/>"
                "</body>"
                "</html>";

    doc.setHtml(text);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}
