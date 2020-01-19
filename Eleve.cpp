#include "Eleve.h"

Eleve::Eleve()
{
    //ctor
}

Eleve::Eleve(QString _id,QString _nom,QString _prenom,int _age,QString _sexe,QString _login,QString _password,QString _contact):
    Personne(_id,_nom,_prenom,_age,_sexe,_login,_password,_contact)
{

}


Eleve::~Eleve()
{
    //dtor
}
