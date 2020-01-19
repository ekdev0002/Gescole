#ifndef COMMENTAIRE_H
#define COMMENTAIRE_H
#include <QString>

class Commentaire
{
    public:
        Commentaire();
        Commentaire( QString _id, QString _text, QString _date, QString _idAuteur, QString _idCandidature);
        virtual ~Commentaire();

        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString Gettext() { return text; }
        void Settext(QString val) { text = val; }
        QString Getdate() { return date; }
        void Setdate(QString val) { date = val; }
        QString GetidAuteur() { return idAuteur; }
        void SetidAuteur(QString val) { idAuteur = val; }
        QString GetidCandidature() { return idCandidature; }
        void SetidCandidature(QString val) { idCandidature = val; }

    protected:

    private:
        QString id;
        QString text;
        QString date;
        QString idAuteur;
        QString idCandidature;
};

#endif // COMMENTAIRE_H
