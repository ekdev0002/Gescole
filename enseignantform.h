#ifndef ENSEIGNANTFORM_H
#define ENSEIGNANTFORM_H

#include <QWidget>
#include "Enseignant.h"
#include "service.h"
#include <QTreeWidget>

namespace Ui {
class EnseignantForm;
}

class EnseignantForm : public QWidget
{
    Q_OBJECT

public:
    explicit EnseignantForm(QTreeWidgetItem * _treeItem,QWidget *parent = nullptr);
    ~EnseignantForm();

private slots:
    void valider();
    void annuler();


private:
    Ui::EnseignantForm *ui;
    QTreeWidgetItem * treeItem;
};

#endif // ENSEIGNANTFORM_H
