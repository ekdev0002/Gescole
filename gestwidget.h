#ifndef GESTWIDGET_H
#define GESTWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <vector>
#include <QMessageBox>
#include "enseignantform.h"
#include "candidatureform.h"
#include "creermatiere.h"
#include "creerclasse.h"
#include "creereleve.h"
#include "Enseignant.h"
#include "Classe.h"
#include "Eleve.h"
#include "Matiere.h"
#include "Candidature.h"
#include "service.h"

namespace Ui {
class GestWidget;
}

class GestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GestWidget(QWidget *parent = nullptr);
    ~GestWidget();
    QTreeWidgetItem* addTreeRoot(QString name, QString description);
    void addTreeChild(int idParent,QString name, QString description);
    void initialData();

private:
    Ui::GestWidget *ui;
    std::vector <QTreeWidgetItem*> listRoot;


private slots:
    void ajouter();
    void modifier();
};

#endif // GESTWIDGET_H
