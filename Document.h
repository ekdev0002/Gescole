#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <QString>

class Document
{
    public:
        Document();
        Document(QString _id,QString _libelle, QString _url,QString _idCandidature);
        virtual ~Document();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString Getlibelle() { return libelle; }
        void Setlibelle(QString val) { libelle = val; }
        QString Geturl() { return url; }
        void Seturl(QString val) { url = val; }
        QString GetidCandidature() { return idCandidature; }
        void SetidCandidature(QString val) { idCandidature = val; }

    protected:

    private:
        QString id;
        QString libelle;
        QString url;
        QString idCandidature;
};

#endif // DOCUMENT_H
