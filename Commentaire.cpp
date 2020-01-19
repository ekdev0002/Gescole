#include "Commentaire.h"

Commentaire::Commentaire()
{

}

Commentaire::Commentaire( QString _id, QString _text, QString _date, QString _idAuteur, QString _idCandidature):
    id(_id), text(_text) ,date (_date),idAuteur (_idAuteur), idCandidature (_idCandidature)
{
    //ctor
}

Commentaire::~Commentaire()
{
    //dtor
}
