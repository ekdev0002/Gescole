#include "Personne.h"

Personne::Personne()
{
    //ctor
}

Personne::Personne(QString _id,QString _nom,QString _prenom,int _age,QString _sexe,QString _login,QString _password,QString _contact):
    id(_id),nom(_nom),prenom(_prenom), login (_login), password(_password), sexe (_sexe), age (_age),contact(_contact)
{
    //ctor
}

Personne::~Personne()
{
    //dtor
}
