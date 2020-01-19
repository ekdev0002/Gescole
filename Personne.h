#ifndef PERSONNE_H
#define PERSONNE_H

#include <QString>

class Personne
{
    public:
        Personne();
        virtual ~Personne();
        Personne(QString _id,QString _nom,QString _prenom,int _age,QString _sexe,QString _login,QString _password,QString _contact);


        QString Getid() { return id; }
        void Setid(QString val) { id = val; }
        QString Getnom() { return nom; }
        void Setnom(QString val) { nom = val; }
        QString Getprenom() { return prenom; }
        void Setprenom(QString val) { prenom = val; }
        QString Getlogin() { return login; }
        void Setlogin(QString val) { login = val; }
        QString Getpassword() { return password; }
        void Setpassword(QString val) { password = val; }
        QString Getsexe() { return sexe; }
        void Setsexe(QString val) { sexe = val; }
        QString Getcontact() { return contact; }
        void Setcontact(QString val) { contact = val; }
        int Getage() { return age; }
        void Setage(int val) { age = val; }

    protected:
        QString id;
        QString nom;
        QString prenom;
        QString login;
        QString password;
        QString sexe;
        QString contact;
        int age;

    private:
};

#endif // PERSONNE_H
