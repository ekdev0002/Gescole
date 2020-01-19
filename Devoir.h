#ifndef DEVOIR_H
#define DEVOIR_H

#include<QString>
#include<QDateTime>

class Devoir
{
    public:
        Devoir();
        virtual ~Devoir();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QDateTime GetdateHeure() { return dateHeure; }
        void SetdateHeure(QDateTime val) { dateHeure = val; }
        QString GetidMatiere() { return idMatiere; }
        void SetidMatiere(QString val) { idMatiere = val; }
        int Getduree() { return duree; }
        void Setduree(int val) { duree = val; }
        QString GetlibMatiere() { return libMatiere; }
        void SetlibMatiere(QString val) { libMatiere = val; }

    protected:
        QString id;
        QDateTime dateHeure;
        QString idMatiere;
        QString libMatiere;
        int duree;

    private:
};

#endif // DEVOIR_H
