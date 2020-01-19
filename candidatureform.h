#ifndef CANDIDATUREFORM_H
#define CANDIDATUREFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include "Candidature.h"
#include <QTreeWidget>
#include "service.h"
#include "Document.h"
#include "commtform.h"
#include "commtform.h"
#include "Commentaire.h"
#include "candidat.h"
#include <QGroupBox>


namespace Ui {
class CandidatureForm;
}

class CandidatureForm : public QWidget
{
    Q_OBJECT

public:
    explicit CandidatureForm(QString _idCandidature,QTreeWidgetItem *_treeItemCand,QWidget *parent = nullptr);
    explicit CandidatureForm(int i,QTreeWidgetItem *_treeItemCand,QWidget *parent = nullptr);
    explicit CandidatureForm(int _i,int _j,QTreeWidgetItem *_treeItem,QWidget *parent);
    ~CandidatureForm();

private slots:
    void submitFile();
    //void suppFile();
    void addComment();
    void telecharger();
    void valider();
    void quitter();
    void changerStatutclose(int a);
    void changerStatutaccept(int a);
    void changerStatutrefus(int a);

private:
    Ui::CandidatureForm *ui;
    QTreeWidgetItem *treeItem;
    std::vector <Document*> listDoc;
    std::vector  <Commentaire*> listCom;
    QString idCandidature;
    int indice;
    std::vector  <QTreeWidgetItem*> listDocWidget;


};

#endif // CANDIDATUREFORM_H
