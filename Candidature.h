#ifndef CANDIDATURE_H
#define CANDIDATURE_H

#include <QString>
#include <vector>
#include "Document.h"
#include "Commentaire.h"

class Candidature
{
    public:
        Candidature();

        virtual ~Candidature();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString GetidClasse() { return idClasse; }
        void SetidClasse(QString val) { idClasse = val; }
        QString GetidProfesseur() { return idProfesseur; }
        void SetidProfesseur(QString val) { idProfesseur = val; }
        std::vector <Document*> GetlisteDocument() { return listeDocument; }
        void SetlisteDocument(std::vector <Document*> val) { listeDocument = val; }
        std::vector <Commentaire*> Getcommentaires() { return listeCommentaires; }
        void Setcommentaires(std::vector <Commentaire*> val) { listeCommentaires = val; }
        QString GetstatutAccepte() { return statutAccepte; }
        void SetstatutAccepte(QString val) { statutAccepte = val; }
        QString GetstatutClose() { return statutClose; }
        void SetstatutClose(QString val) { statutClose = val; }


    protected:

    private:
        QString id;
        QString idClasse;
        QString idProfesseur;
        std::vector <Document*> listeDocument;
        std::vector <Commentaire*> listeCommentaires;
        QString statutAccepte;
        QString statutClose;
};

#endif // CANDIDATURE_H
