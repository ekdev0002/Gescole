#ifndef NOTE_H
#define NOTE_H

#include<QString>
class Note
{
    public:
        Note();
        virtual ~Note();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString GetidMatiere() { return idMatiere; }
        void SetidMatiere(QString val) { idMatiere = val; }
        float Getnote() { return note; }
        void Setnote(float val) { note = val; }
        int Getcoef() { return coef; }
        void Setcoef(int val) { coef = val; }
        QString GetidEleve() { return idEleve; }
        void SetidEleve(QString val) { idEleve = val; }
        QString Getintitule() { return intitule; }
        void Setintitule(QString val) { intitule = val; }

    protected:

    private:
        QString id;
        QString idMatiere;
        float note;
        int coef;
        QString idEleve;
        QString intitule;
};

#endif // NOTE_H
