#ifndef COURSFORM_H
#define COURSFORM_H

#include <QWidget>
#include "service.h"
#include <QCalendarWidget>
#include <QTextCharFormat>

namespace Ui {
class CoursForm;
}

class CoursForm : public QWidget
{
    Q_OBJECT

public:
    explicit CoursForm(QCalendarWidget * _calWidget,QWidget *parent = nullptr);
    ~CoursForm();

private slots:
    void valider();
    void annuler();

private:
    Ui::CoursForm *ui;
    QCalendarWidget * calWidget;
};

#endif // COURSFORM_H
