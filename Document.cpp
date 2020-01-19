#include "Document.h"


Document::Document()
{

}
Document::Document(QString _id,QString _libelle, QString _url,QString _idCandidature):id(_id),
    libelle(_libelle), url(_url), idCandidature(_idCandidature)
{
    //ctor
}

Document::~Document()
{
    //dtor
}
