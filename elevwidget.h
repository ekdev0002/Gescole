#ifndef ELEVWIDGET_H
#define ELEVWIDGET_H

#include <QWidget>
#include "service.h"
#include <QMessageBox>
#include <QTextFormat>
#include "Planning.h"
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>


namespace Ui {
class elevWidget;
}

class elevWidget : public QWidget
{
    Q_OBJECT

public:
    explicit elevWidget(QWidget *parent = nullptr);
    ~elevWidget();

private:
    Ui::elevWidget *ui;
        Planning  * planning;
        std:: vector <QString> listMatiere;
        std:: vector <float> listNote;
        std:: vector <float> listCoef;
        std:: vector <float> listNotePond;
        QString classe;
        QString effectif;
        float totalNote;
        float totalNotePond;
        int totalCoef;

private slots:
    void info();
    void imprimer();
};

#endif // ELEVWIDGET_H
