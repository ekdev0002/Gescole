#ifndef DEVFORM_H
#define DEVFORM_H

#include <QWidget>
#include "service.h"
#include <QCalendarWidget>
#include <QTextCharFormat>

namespace Ui {
class DevForm;
}

class DevForm : public QWidget
{
    Q_OBJECT

public:
    explicit DevForm(QCalendarWidget * _calWidget,QWidget *parent = nullptr);
    ~DevForm();

private slots:
    void valider();
    void annuler();


private:
    Ui::DevForm *ui;
    QCalendarWidget * calWidget;

};

#endif // DEVFORM_H
