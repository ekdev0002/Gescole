#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include "Personne.h"


class Gestionnaire : public Personne
{
    public:
        Gestionnaire();
        Gestionnaire(QString _id,QString _nom,QString _prenom,int _age,QString _sexe,QString _login,QString _password,QString _contact);
        virtual ~Gestionnaire();

    protected:

    private:
};

#endif // GESTIONNAIRE_H
