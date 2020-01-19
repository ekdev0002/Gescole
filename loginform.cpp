#include "loginform.h"
#include "ui_loginform.h"

#include "mainwindow.h"


#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    this->mainWindow = new MainWindow();

    connect(ui->pushButtonSubmit, SIGNAL(clicked()), this, SLOT(submit()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::submit()
{
    if(this->mainWindow->lancer(Service::chercherPersonne(ui->statut->currentText(),ui->lineEditLogin->text(),ui->lineEditPassword->text())))
    {
        this->close();
        this->mainWindow->show();
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Erreur de connexion! ");
    }
}

void LoginForm::cancel()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                          "Confirm exit",
                          "Are you sure to close ?"))
    {
        close();
    }
}
