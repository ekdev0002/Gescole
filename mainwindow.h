#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "Personne.h"
#include "Gestionnaire.h"
#include "Enseignant.h"
#include "Eleve.h"
#include "gestwidget.h"
#include "enseignantwidget.h"
#include "elevwidget.h"



#include <QtSql>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
     ~MainWindow();

    int lancer(Personne * utilisateur);
private slots:


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
