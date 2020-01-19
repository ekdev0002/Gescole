#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include "Personne.h"



class Enseignant : public Personne
{
    public:
        Enseignant();
        Enseignant(QString _id,QString _nom,QString _prenom,int _age,QString _sexe,QString _login,QString _password,QString _contact);
        virtual ~Enseignant();

    protected:

    private:
};

#endif // ENSEIGNANT_H
