#ifndef CREERCLASSE_H
#define CREERCLASSE_H

#include <QWidget>
#include <QTreeWidget>
#include <vector>
#include "Classe.h"
#include "service.h"
#include <QVariant>

namespace Ui {
class CreerClasse;
}

class CreerClasse : public QWidget
{
    Q_OBJECT

public:
    explicit CreerClasse(QTreeWidgetItem * _treeItem,QWidget *parent = nullptr);
    ~CreerClasse();

private slots:
    void submit();
    void cancel();

private:
    Ui::CreerClasse *ui;
    QTreeWidgetItem *treeItem;
};

#endif // CREERCLASSE_H
