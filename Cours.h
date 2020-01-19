#ifndef COURS_H
#define COURS_H
#include<QString>
#include <QDateTime>
class Cours
{
    public:
        Cours();
        virtual ~Cours();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString GetidMatiere() { return idMatiere; }
        void SetidMatiere(QString val) { idMatiere = val; }
        QDateTime GetDateHeure() { return DateHeure; }
        void SetDateHeure(QDateTime val) { DateHeure = val; }
        int Getduree() { return duree; }
        void Setduree(int val) { duree = val; }
        QString GetlibMatiere() { return libMatiere; }
        void SetlibMatiere(QString val) { libMatiere = val; }

    protected:
        QString id;
        QString idMatiere;
        QDateTime DateHeure;
        QString libMatiere;
        int duree;

    private:
};

#endif // COURS_H
