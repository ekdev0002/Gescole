#ifndef BULLETIN_H
#define BULLETIN_H
#include <QString>
#include "Note.h"
#include<vector>

class Bulletin
{
    public:
        Bulletin();
        virtual ~Bulletin();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString GetidEleve() { return idEleve; }
        void SetidEleve(QString val) { idEleve = val; }
        int Getrang() { return rang; }
        void Setrang(int val) { rang = val; }
        float Getmoyenne() { return moyenne; }
        void Setmoyenne(float val) { moyenne = val; }
        QString Getdecision() { return decision; }
        void Setdecision(QString val) { decision = val; }

    protected:

    private:
        QString id;
        float moyenne;
        int rang;
        QString decision;
        QString idEleve;
};

#endif // BULLETIN_H
