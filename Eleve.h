#ifndef ELEVE_H
#define ELEVE_H

#include "Personne.h"
#include <QString>


class Eleve : public Personne
{
    public:
        Eleve();
        Eleve(QString _id,QString _nom,QString _prenom,int _age,QString _sexe,QString _login,QString _password,QString _contact);
        virtual ~Eleve();

        QString GetidClasse() { return idClasse; }
        void SetidClasse(QString val) { idClasse = val; }

    protected:

    private:
        QString idClasse;

};

#endif // ELEVE_H
