#ifndef CLASSE_H
#define CLASSE_H

#include <QString>
#include <vector>
#include <Eleve.h>
#include <Matiere.h>


class Classe
{
    public:
        Classe();
        Classe(QString _id,QString _libelle,int _effectif);
        virtual ~Classe();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString Getlibelle() { return libelle; }
        void Setlibelle(QString val) { libelle = val; }
        int Geteffectif() { return effectif; }
        void Seteffectif(int val) { effectif = val; }
        std::vector <Eleve*> GetlisteEleve() { return listeEleve; }
        void SetlisteEleve(std::vector <Eleve*> val) { listeEleve = val; }
        std::vector <Matiere*> GetlisteMatiere() { return listeMatiere; }
        void SetlisteMatiere(std::vector <Matiere*> val) { listeMatiere = val; }

    protected:

    private:
        QString id;
        QString libelle;
        int effectif;
        std::vector <Eleve*> listeEleve;
        std::vector <Matiere*> listeMatiere;
};

#endif // CLASSE_H
