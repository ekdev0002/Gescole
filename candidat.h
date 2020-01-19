#ifndef CANDIDAT_H
#define CANDIDAT_H

#include "Personne.h"

class Candidat:public Personne
{
public:
    Candidat();
    Candidat(QString _id,QString _nom,QString _prenom,int _age,QString _sexe,QString _login,QString _password,QString _contact);
};

#endif // CANDIDAT_H
