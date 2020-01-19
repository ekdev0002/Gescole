#ifndef CREERELEVE_H
#define CREERELEVE_H

#include <QWidget>
#include <QTreeWidget>
#include "service.h"

namespace Ui {
class CreerEleve;
}

class CreerEleve : public QWidget
{
    Q_OBJECT

public:
    explicit CreerEleve(QTreeWidgetItem * _treeItem,QTreeWidgetItem * _treeItemCand,QTreeWidgetItem * _treeItemClasse,QWidget *parent = nullptr);
    ~CreerEleve();

private slots:
    void valider();
    void annuler();
    void change(int a);

private:
    Ui::CreerEleve *ui;
    QTreeWidgetItem * treeItem;
    QTreeWidgetItem * treeItemClasse;
    QTreeWidgetItem * treeItemCand;

};

#endif // CREERELEVE_H
