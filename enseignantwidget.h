#ifndef ENSEIGNANTWIDGET_H
#define ENSEIGNANTWIDGET_H

#include <QWidget>
#include <QPicture>
#include <QTreeWidget>
#include <vector>
#include <QMessageBox>
#include "enseignantform.h"
#include "candidatureform.h"
#include "Enseignant.h"
#include "Classe.h"
#include "Eleve.h"
#include "Matiere.h"
#include "Candidature.h"
#include "service.h"
#include "coursform.h"
#include "devform.h"
#include "Planning.h"
#include "saisirnoteform.h"


namespace Ui {
class enseignantWidget;
}

class enseignantWidget : public QWidget
{
    Q_OBJECT

public:
    explicit enseignantWidget(QWidget *parent = nullptr);
    ~enseignantWidget();
    QTreeWidgetItem* addTreeRoot(QString name, QString description);
    void addTreeChild(int idParent,QString name, QString description);

private slots:
    void modifier();
    void plannifierCours();
    void plannifierDev();
    void info();
    void saisir();

private:
    Ui::enseignantWidget *ui;
    std::vector <QTreeWidgetItem*> listRoot;
    std::vector <QString> listIdMatiere;
    Planning  * planning;

};

#endif // ENSEIGNANTWIDGET_H
