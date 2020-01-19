#ifndef COMMTFORM_H
#define COMMTFORM_H

#include <QWidget>
#include <Commentaire.h>
#include <QTreeWidget>
#include <QMessageBox>
#include "service.h"
#include <QDateTime>

namespace Ui {
class CommtForm;
}

class CommtForm : public QWidget
{
    Q_OBJECT

public:
    explicit CommtForm(QString _idCandidature,QTreeWidgetItem *_treeComt,std::vector <Commentaire*> * _listCom,QWidget *parent = nullptr);
    ~CommtForm();


private slots:
    void valider();
private:
    Ui::CommtForm *ui;
    QString idCandidature;
    QTreeWidgetItem *treeComt;
    std::vector <Commentaire*> * listCom;
};

#endif // COMMTFORM_H
