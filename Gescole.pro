#-------------------------------------------------
#
# Project created by QtCreator 2019-02-19T13:35:12
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetQt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Eleve.cpp \
    Enseignant.cpp \
    Gestionnaire.cpp \
    gestwidget.cpp \
    loginform.cpp \
    Personne.cpp \
    service.cpp \
    candidatureform.cpp \
    enseignantform.cpp \
    creermatiere.cpp \
    creerclasse.cpp \
    creereleve.cpp \
    Classe.cpp \
    Matiere.cpp \
    Candidature.cpp \
    Document.cpp \
    Commentaire.cpp \
    commtform.cpp \
    Bulletin.cpp \
    Cours.cpp \
    Devoir.cpp \
    Note.cpp \
    Planning.cpp \
    candidat.cpp \
    enseignantwidget.cpp \
    elevwidget.cpp \
    devform.cpp \
    coursform.cpp \
    saisirnoteform.cpp \
    mythread.cpp

HEADERS += \
        mainwindow.h \
    Eleve.h \
    Enseignant.h \
    Gestionnaire.h \
    gestwidget.h \
    loginform.h \
    Personne.h \
    service.h \
    candidatureform.h \
    enseignantform.h \
    creermatiere.h \
    creerclasse.h \
    creereleve.h \
    Classe.h \
    Matiere.h \
    Candidature.h \
    Document.h \
    Commentaire.h \
    commtform.h \
    Bulletin.h \
    Cours.h \
    Devoir.h \
    Note.h \
    Planning.h \
    candidat.h \
    enseignantwidget.h \
    elevwidget.h \
    devform.h \
    coursform.h \
    saisirnoteform.h \
    mythread.h

FORMS += \
        mainwindow.ui \
    gestwidget.ui \
    loginform.ui \
    candidatureform.ui \
    enseignantform.ui \
    creermatiere.ui \
    creerclasse.ui \
    creereleve.ui \
    commtform.ui \
    enseignantwidget.ui \
    elevwidget.ui \
    devform.ui \
    coursform.ui \
    saisirnoteform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    test.qrc

DISTFILES +=
