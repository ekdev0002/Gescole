#ifndef SERVICE_H
#define SERVICE_H

#include <QtSql/qsqldatabase.h>
#include <QtSql>
#include <QString>
#include "Personne.h"
#include "Gestionnaire.h"
#include <ctime>
#include "Bulletin.h"
#include "Cours.h"
#include "Classe.h"
#include "Candidature.h"
#include "Commentaire.h"
#include "Document.h"
#include "Devoir.h"
#include "Eleve.h"
#include "Enseignant.h"
#include "Matiere.h"
#include "Note.h"
#include "candidat.h"
#include "Planning.h"
#include <vector>


class Service
{
public:

    static Personne * chercherPersonne(QString status,QString login,QString password);

    static QString genererId();
    static void closeDB();

    static std::vector <Classe*> GetlistClassFromDB();
    static std::vector <Matiere*> GetlistMatiereFromDB();
    static std::vector <Enseignant*> GetlistEnsFromDB();
    static std::vector <Candidat*> GetlistCandtFromDB();
    static std::vector <Candidature*> GetlistCandidatureFromDB();
    static std::vector <Eleve*> GetlistElevFromDB();
    static std::vector <Document*> GetlistDocumentFromDB();
    static std::vector <Commentaire*> GetlistCommentaireFromDB();
    static std::vector <Cours*> GetlistCoursFromDB();
    static std::vector <Devoir*> GetlistDevoirFromDB();
    static std::vector <Note*> GetlistNoteFromDB();
    static std::vector <Bulletin*> GetlistBulletinFromDB();

    static std::vector <Matiere*> GetlistMatiereFromDBforEns();
    static std::vector <Matiere*> GetlistMatiereFromDBforElev();
    static std::vector <Candidature*> GetlistCandidatureFromDBforEns();



    static std::vector <Classe*> GetlistClass();
    static std::vector <Matiere*> GetlistMatiere();
    static std::vector <Enseignant*> GetlistEns();
    static std::vector <Candidat*> GetlistCandt();
    static std::vector <Candidature*> GetlistCandidature();
    static std::vector <Eleve*> GetlistElev();
    static std::vector <Document*> GetlistDocument();
    static std::vector <Commentaire*> GetlistCommentaire();
    static std::vector <Cours*> GetlistCours();
    static std::vector <Devoir*> GetlistDevoir();
    static std::vector <Note*> GetlistNote();
    static std::vector <Bulletin*> GetlistBulletin();

    static Personne * GetutilisateurCourant() {return utilisateurCourant;};
    static Eleve * GetutilisateurCourant(int a) {return utilisateurEleve;};

    static void addClass(Classe * val){ listClass.push_back(val);};
    static void addMatiere(Matiere * val){ listMatiere.push_back(val);};
    static void addEns(Enseignant * val){ listEns.push_back(val);};
    static void addCandt(Candidat * val){ listCandt.push_back(val);};
    static void addCandidature(Candidature * val){ listCandidature.push_back(val);};
    static void addElev(Eleve * val){ listElev.push_back(val);};
    static void addDocument(Document * val){ listDocument.push_back(val);};
    static void addCommentaire(Commentaire * val){ listComt.push_back(val);};


    static void Persister(Classe *val);
    static void Persister(Candidature *val);
     static void Persister(Candidat *val);
    static void Persister(Commentaire *val);
    static void Persister(Enseignant *val);
    static void Persister(Document *val);
    static void Persister(Matiere *val);
    static void Persister(Eleve *val);
    static void Persister(Cours *val);
    static void Persister(Devoir *val);
    static void Persister(Note *val);
    static void Persister(Bulletin *val);
    static void Persister(std::vector <Note*> val);
    static void Nettoyage();

    static QString classement(QString moyenne,QString idClasse);



private:


    Service();
    ~Service();
    static Personne * utilisateurCourant;
    static Eleve * utilisateurEleve;
    static QSqlDatabase db;
    static std::vector <Classe*> listClass;
    static std::vector <Matiere*> listMatiere;
    static std::vector <Enseignant*> listEns;
    static std::vector <Candidat*> listCandt;
    static std::vector <Candidature*> listCandidature;
    static std::vector <Eleve*> listElev;
    static std::vector <Document*> listDocument;
    static std::vector <Commentaire*> listComt;
    static std::vector <Cours*> listCours;
    static std::vector <Devoir*> listDev;
    static std::vector <Note*> listNote;
    static std::vector <Bulletin*> listBulletin;
};

#endif // SERVICE_H
