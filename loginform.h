#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void submit();
    void cancel();

private:
    Ui::LoginForm *ui;
    MainWindow * mainWindow;
};

#endif // LOGINFORM_H
