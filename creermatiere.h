#ifndef CREERMATIERE_H
#define CREERMATIERE_H

#include <QWidget>
#include "service.h"
#include <QTreeWidget>

namespace Ui {
class CreerMatiere;
}

class CreerMatiere : public QWidget
{
    Q_OBJECT

public:
    explicit CreerMatiere(QTreeWidgetItem * _treeItem,QWidget *parent = nullptr);
    ~CreerMatiere();

private slots:
    void valider();
    void annuler();

private:
    Ui::CreerMatiere *ui;
    QTreeWidgetItem * treeItem;
};

#endif // CREERMATIERE_H
