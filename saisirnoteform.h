#ifndef SAISIRNOTEFORM_H
#define SAISIRNOTEFORM_H
#include "service.h"
#include <QLabel>
#include <QDoubleSpinBox>

#include <QWidget>
#include <vector>

namespace Ui {
class SaisirNoteForm;
}

class SaisirNoteForm : public QWidget
{
    Q_OBJECT

public:
    explicit SaisirNoteForm(QString _idMatiere,QWidget *parent = nullptr);
    ~SaisirNoteForm();

public slots:
    void valider();
    void annuler();

private:
    Ui::SaisirNoteForm *ui;
    QString idMatiere;
    std::vector <QDoubleSpinBox*> listSpin;
    std::vector <Eleve*> listEleve;
    int coef;

};

#endif // SAISIRNOTEFORM_H
