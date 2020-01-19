#include "mainwindow.h"
#include <QApplication>
#include "loginform.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap image(":/new/prefix1/images/workspace1.jpg");
    QBrush brush(image);
    QPalette palette;
    palette.setBrush(QPalette::Window,brush);
    qApp->setPalette(palette);

    //fenetre de login
    LoginForm loginForm;
    loginForm.show();
    return a.exec();
}
