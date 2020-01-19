#ifndef MATIERE_H
#define MATIERE_H

#include <QString>

class Matiere
{
    public:
        Matiere();
        virtual ~Matiere();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString Getlibelle() { return libelle; }
        void Setlibelle(QString val) { libelle = val; }
        QString GetidProfesseur() { return idProfesseur; }
        void SetidProfesseur(QString val) { idProfesseur = val; }
        QString GetidClasse() { return idClasse; }
        void SetidClasse(QString val) { idClasse = val; }
        int Getcoef() { return coef; }
        void Setcoef(int val) { coef = val; }

    protected:

    private:
        QString id;
        QString libelle;
        QString idProfesseur;
        QString idClasse;
        int coef;
};

#endif // MATIERE_H
