#include "service.h"
#include <string.h>

#include <iostream>

QSqlDatabase Service::db = QSqlDatabase::addDatabase("QMYSQL");
Personne * Service::utilisateurCourant=new Personne();
std::vector <Classe*> Service::listClass;
std::vector <Matiere*> Service::listMatiere;
std::vector <Enseignant*> Service::listEns;
std::vector <Candidat*> Service::listCandt;
std::vector <Candidature*> Service::listCandidature;
std::vector <Eleve*> Service::listElev;
std::vector <Document*> Service::listDocument;
std::vector <Commentaire*> Service::listComt;
std::vector <Cours*> Service::listCours;
std::vector <Devoir*> Service::listDev;
std::vector <Note*> Service::listNote;
std::vector <Bulletin*> Service::listBulletin;
Eleve * Service::utilisateurEleve;

Service::Service()
{
}


void Service::Nettoyage()
{
    for (int i = 0; i < listClass.size(); ++i) {
        delete listClass[i];
    }
    for (int i = 0; i < listMatiere.size(); ++i) {
        delete listMatiere[i];
    }
    for (int i = 0; i < listEns.size(); ++i) {
        delete listEns[i];
    }
    for (int i = 0; i < listCandt.size(); ++i) {
        delete listCandt[i];
    }
    for (int i = 0; i < listCandidature.size(); ++i) {
        delete listCandidature[i];
    }
    for (int i = 0; i < listElev.size(); ++i) {
        delete listElev[i];
    }
    for (int i = 0; i < listDocument.size(); ++i) {
        delete listDocument[i];
    }
    for (int i = 0; i < listComt.size(); ++i) {
        delete listComt[i];
    }
    for (int i = 0; i < listCours.size(); ++i) {
        delete listCours[i];
    }
    for (int i = 0; i < listDev.size(); ++i) {
        delete listDev[i];
    }
}


Personne * Service::chercherPersonne(QString status,QString login,QString password)
{
    QString listMot[10];
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("a1l2l3eric");
    db.setDatabaseName("gescole");

    if(db.open())
    {
        std::cout << "Connexion réussie à " << db.hostName().toStdString() << std::endl;
        QSqlQuery query;
        QString requete="SELECT * FROM gescole."+status;
           if(query.exec(requete))
           {
              while ( query.next() )
              {
                 for(int i=0;i<query.record().count();i++)
                    {
                     listMot[i]=query.value(i).toString();
                    }
                 if(listMot[5]==login && listMot[6]==password)
                 {
                     qDebug() << listMot[5]<<" "<<listMot[6] << " " << listMot[7];
                     //creation de l'utisateur et initialisation de l'application


                     if(status=="Gestionnaire")
                     {
                        utilisateurCourant= new Gestionnaire(listMot[0],listMot[1],listMot[2],listMot[3].toInt(),listMot[4],listMot[5],listMot[6],listMot[7]);
                        listClass=GetlistClassFromDB();//liste des classes
                        listElev=GetlistElevFromDB();//liste des eleves
                        listEns=GetlistEnsFromDB();//liste des enseignants
                        listComt=GetlistCommentaireFromDB();//liste des commentaires
                        listDocument=GetlistDocumentFromDB();//liste des documents
                        listCandidature=GetlistCandidatureFromDB();//liste de candidature
                         listCandt=GetlistCandtFromDB();//liste des candidats
                        listMatiere=GetlistMatiereFromDB();//liste des matieres

                     }
                     else if(status=="Enseignant")
                     {
                         utilisateurCourant= new Enseignant(listMot[0],listMot[1],listMot[2],listMot[3].toInt(),listMot[4],listMot[5],listMot[6],listMot[7]);
                         listClass=GetlistClassFromDB();//liste des classes
                         listElev=GetlistElevFromDB();//liste des eleves
                         listEns=GetlistEnsFromDB();//liste des enseignants
                         listComt=GetlistCommentaireFromDB();//liste des commentaires
                         listDocument=GetlistDocumentFromDB();//liste des documents
                         listCandidature=GetlistCandidatureFromDBforEns();//liste de candidature
                          listCandt=GetlistCandtFromDB();//liste des candidats
                         listMatiere=GetlistMatiereFromDBforEns();//liste des matieres
                         listCours=GetlistCoursFromDB();
                         listDev=GetlistDevoirFromDB();


                     }
                     else
                     {
                         utilisateurEleve= new Eleve(listMot[0],listMot[1],listMot[2],listMot[3].toInt(),listMot[4],listMot[5],listMot[6],listMot[8]);
                         utilisateurEleve->SetidClasse(listMot[7]);
                         listClass=GetlistClassFromDB();//liste des classes
                         listEns=GetlistEnsFromDB();//liste des enseignants
                         listComt=GetlistCommentaireFromDB();//liste des commentaires
                         listDocument=GetlistDocumentFromDB();//liste des documents
                         listCandidature=GetlistCandidatureFromDB();//liste de candidature
                          listCandt=GetlistCandtFromDB();//liste des candidats
                         listMatiere=GetlistMatiereFromDBforElev();//liste des matieres
                         listCours=GetlistCoursFromDB();
                         listDev=GetlistDevoirFromDB();
                         listNote=GetlistNoteFromDB();
                         return  utilisateurEleve;

                     }

                     return utilisateurCourant;


              }
              else
             {
               qDebug () << " Personne introuvable dans la base de donnee";
                }
           }
           }
    }
    else
    {
        std::cout << "La connexion a échouée !" << std::endl;

    }
    return new Personne();
}

QString Service::genererId()
{
    QString format = "yyyyMMddHHmmss"; //je définit le format que je veux
    return QDateTime::currentDateTime().toString(format);
}

void Service::closeDB()
{
    db.close();
}


 void Service::Persister(Classe *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.classe (id,effectif,libelle) VALUES (:id,:effectif,:libelle)");
     query.bindValue(":id",val->Getid());
     query.bindValue(":effectif",val->Geteffectif());
     query.bindValue(":libelle",val->Getlibelle());
     if (query.exec())
       {
            listClass.push_back(val);
           qDebug() << "Insertion réussie" << endl;
       }
       else
       {
           qDebug() << "Echec Insertion " << endl;
           qDebug() << query.lastError().text();
       }

 }
 void Service::Persister(Candidature *val)
 {
     QSqlQuery query;
     bool reponse=false;
     QString requete="SELECT id FROM gescole.Candidature";
        if(query.exec(requete))
        {
           while ( query.next() )
           {
              if(query.value(0).toString()==val->Getid())
                 {
                  reponse=true;
                 }
           }
        }

         if(!reponse)
         {
             query.prepare("INSERT INTO gescole.candidature (id,idClasse,idProfesseur,statutAccepte,statutClose) VALUES (:id,:idClasse,:idProfesseur,:statutAccepte,:statutClose)");
             query.bindValue(":id",val->Getid());
              query.bindValue(":idClasse",val->GetidClasse());
             query.bindValue(":idProfesseur",val->GetidProfesseur());
             query.bindValue(":statutAccepte",val->GetstatutAccepte());
             query.bindValue(":statutClose",val->GetstatutClose());
             if (query.exec())
               {
                    listCandidature.push_back(val);
                   qDebug() << "Insertion réussie de candidature" << endl;
               }
               else
               {
                   qDebug() << "Echec Insertion de candidature " << endl;
                   qDebug() << query.lastError().text();
               }
         }
         else
         {
             query.prepare("UPDATE gescole.candidature SET idClasse=:idClasse,idProfesseur=:idProfesseur,statutAccepte=:statutAccepte,statutClose=:statutClose WHERE id=:id");
             query.bindValue(":id",val->Getid());
              query.bindValue(":idClasse",val->GetidClasse());
             query.bindValue(":idProfesseur",val->GetidProfesseur());
             query.bindValue(":statutAccepte",val->GetstatutAccepte());
             query.bindValue(":statutClose",val->GetstatutClose());
             if (query.exec())
               {
                 for(int i=0;i<listCandidature.size();i++)
                 {
                     if(listCandidature[i]->Getid()==val->Getid())
                         listCandidature[i]=val;
                 }
                   qDebug() << "Mise à jour réussie de candidature" << endl;
               }
               else
               {
                   qDebug() << "Echec de Mise à jour de candidature " << endl;
                   qDebug() << query.lastError().text();
               }

         }

 }


 void Service::Persister(Bulletin *val)
 {
     QSqlQuery query;
     bool reponse=false;
     QString requete="SELECT id FROM gescole.Bulletin";
        if(query.exec(requete))
        {
           while ( query.next() )
           {
              if(query.value(0).toString()==val->Getid())
                 {
                  reponse=true;
                 }
           }
        }

         if(!reponse)
         {
             query.prepare("INSERT INTO gescole.bulletin (id,moyenne,rang,decision,idEleve) VALUES (:id,:moyenne,:rang,:decision,:idEleve)");
             query.bindValue(":id",val->Getid());
              query.bindValue(":moyenne",val->Getmoyenne());
             query.bindValue(":rang",val->Getrang());
             query.bindValue(":decision",val->Getdecision());
             query.bindValue(":idEleve",val->GetidEleve());
             if (query.exec())
               {
                    listBulletin.push_back(val);
                   qDebug() << "Insertion réussie de candidature" << endl;
               }
               else
               {
                   qDebug() << "Echec Insertion de candidature " << endl;
                   qDebug() << query.lastError().text();
               }
         }
         else
         {
             query.prepare("UPDATE gescole.bulletin SET moyenne=:moyenne,rang=:rang,decision=:decision,idEleve=:idEleve WHERE id=:id");
             query.bindValue(":id",val->Getid());
             query.bindValue(":moyenne",val->Getmoyenne());
             query.bindValue(":rang",val->Getrang());
             query.bindValue(":decision",val->Getdecision());
             query.bindValue(":idEleve",val->GetidEleve());
             if (query.exec())
               {
                 for(int i=0;i<listBulletin.size();i++)
                 {
                     if(listBulletin[i]->Getid()==val->Getid())
                         listBulletin[i]=val;
                 }
                   qDebug() << "Mise à jour réussie de candidature" << endl;
               }
               else
               {
                   qDebug() << "Echec de Mise à jour de candidature " << endl;
                   qDebug() << query.lastError().text();
               }

         }

 }



 void Service::Persister(Document *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.document (id,libelle,url,idCandidature) VALUES (:id,:libelle,:url,:idCandidature)");
     query.bindValue(":id",val->Getid());
     query.bindValue(":libelle",val->Getlibelle());
     query.bindValue(":url",val->Geturl());
     query.bindValue(":idCandidature",val->GetidCandidature());
     if (query.exec())
       {
            listDocument.push_back(val);
           qDebug() << "Insertion réussie" << endl;
       }
       else
       {
           qDebug() << "Echec Insertion " << endl;
           qDebug() << query.lastError().text();
       }

 }
 void Service::Persister(Matiere *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.matiere (id,libelle,idProfesseur,idClasse,coef) VALUES (:id,:libelle,:idProfesseur,:idClasse,:coef)");
     query.bindValue(":id",val->Getid());
     query.bindValue(":libelle",val->Getlibelle());
     query.bindValue(":idProfesseur",val->GetidProfesseur());
     query.bindValue(":idClasse",val->GetidClasse());
     query.bindValue(":coef",val->Getcoef());
     qDebug() << val->GetidProfesseur();
     if (query.exec())
       {
           listMatiere.push_back(val);
           qDebug() << "Insertion réussie" << endl;
       }
       else
       {
           qDebug() << "Echec Insertion " << endl;
           qDebug() << query.lastError().text();
       }

 }

 void Service::Persister(Commentaire *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.commentaire (id,text,dateHeure,idAuteur,idCandidature) VALUES (:id,:text,:dateHeure,:idAuteur,:idCandidature)");
     query.bindValue(":id",val->Getid());
     query.bindValue(":text",val->Gettext());
     query.bindValue(":dateHeure",val->Getdate());
     query.bindValue(":idAuteur",val->GetidAuteur());
     query.bindValue(":idCandidature",val->GetidCandidature());
     if (query.exec())
       {
         listComt.push_back(val);
         qDebug() << "Insertion réussie" << endl;
       }
       else
       {
           qDebug() << "Echec Insertion " << endl;
           qDebug() << query.lastError().text();
       }

 }


 void Service::Persister(Enseignant *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.Enseignant (id,nom,prenom,age,sexe,login,password,contact) VALUES (:id,:nom,:prenom,:age,:sexe,:login,:password,:contact)");
     query.bindValue(":id",val->Getid());
     query.bindValue(":nom",val->Getnom());
     query.bindValue(":prenom",val->Getprenom());
     query.bindValue(":age",val->Getage());
     query.bindValue(":sexe",val->Getsexe());
     query.bindValue(":login",val->Getlogin());
     query.bindValue(":password",val->Getpassword());
     query.bindValue(":contact",val->Getcontact());
     if (query.exec())
       {
            listEns.push_back(val);
           qDebug() << "Base de donnee: Insertion réussie" << endl;
       }
       else{
           qDebug() << "Base de donnee: Echec Insertion " << endl;
           qDebug() << query.lastError().text();
       }
 }

 void Service::Persister(Candidat *val)
 {
     QSqlQuery query;
     bool reponse=false;
     QString requete="SELECT id FROM gescole.Candidat";
        if(query.exec(requete))
        {
           while ( query.next() )
           {
              if(query.value(0).toString()==val->Getid())
                 {
                  reponse=true;
                 }
           }
        }

         if(!reponse)
         {
             query.prepare("INSERT INTO gescole.Candidat (id,nom,prenom,age,sexe,login,password,contact) VALUES (:id,:nom,:prenom,:age,:sexe,:login,:password,:contact)");
             query.bindValue(":id",val->Getid());
             query.bindValue(":nom",val->Getnom());
             query.bindValue(":prenom",val->Getprenom());
             query.bindValue(":age",val->Getage());
             query.bindValue(":sexe",val->Getsexe());
             query.bindValue(":login",val->Getlogin());
             query.bindValue(":password",val->Getpassword());
             query.bindValue(":contact",val->Getcontact());
             if (query.exec())
               {
                   listCandt.push_back(val);
                   qDebug() << "Base de donnee: Insertion réussie" << endl;
               }
               else{
                   qDebug() << "Base de donnee: Echec Insertion " << endl;
                   qDebug() << query.lastError().text();
               }
         }
 }

 void Service::Persister(Eleve *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.Eleve (id,nom,prenom,age,sexe,login,password,contact,idClasse) VALUES (:id,:nom,:prenom,:age,:sexe,:login,:password,:contact,:idClasse);UPDATE gescole.classe set effectif=effectif+1 WHERE id=:idClasse");
     query.bindValue(":id",val->Getid());
     query.bindValue(":nom",val->Getnom());
     query.bindValue(":prenom",val->Getprenom());
     query.bindValue(":age",val->Getage());
     query.bindValue(":sexe",val->Getsexe());
     query.bindValue(":login",val->Getlogin());
     query.bindValue(":password",val->Getpassword());
     query.bindValue(":contact",val->Getcontact());
     query.bindValue(":idClasse",val->GetidClasse());
     if (query.exec())
       {
           listElev.push_back(val);
           for (int i=0;i<listClass.size();i++)
           {
               if(listClass[i]->Getid()==val->GetidClasse())
               {
                   listClass[i]->Seteffectif(listClass[i]->Geteffectif()+1);
               }
           }
           qDebug() << "Base de donnee: Insertion réussie d'un eleve" << endl;
       }
       else{
           qDebug() << "Base de donnee: Echec Insertion d'un eleve " << endl;
           qDebug() << query.lastError().text();
       }
 }

 void Service::Persister(Cours *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.cours (id,idMatiere,dateHeure,duree) VALUES (:id,:idMatiere,:dateHeure,:duree)");
     query.bindValue(":id",val->Getid());
     query.bindValue(":idMatiere",val->GetidMatiere());
     query.bindValue(":dateHeure",val->GetDateHeure().toString());
     query.bindValue(":duree",val->Getduree());
     if (query.exec())
       {
           listCours.push_back(val);
           qDebug() << "Base de donnee: Insertion réussie" << endl;
       }
       else{
           qDebug() << "Base de donnee: Echec Insertion " << endl;
           qDebug() << query.lastError().text();
       }
 }



 void Service::Persister(Note *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.Note (id,idMatiere,note,coef,idEleve,intitule) VALUES (:id,:idMatiere,:note,:coef,:idEleve,:intitule)");
     query.bindValue(":id",val->Getid());
     query.bindValue(":idMatiere",val->GetidMatiere());
     query.bindValue(":note",val->Getnote());
     query.bindValue(":coef",val->Getcoef());
     query.bindValue(":idEleve",val->GetidEleve());
     query.bindValue(":intitule",val->Getintitule());
     if (query.exec())
       {
           qDebug() << "Base de donnee: Insertion réussie" << endl;
       }
       else{
           qDebug() << "Base de donnee: Echec Insertion " << endl;
           qDebug() << query.lastError().text();
       }
 }


 void Service::Persister(std::vector <Note*> val)
 {
     for (int i=0;i<val.size();i++)
     {
        Service::Persister(val[i]);
     }

 }

 void Service::Persister(Devoir *val)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO gescole.Devoir (id,idMatiere,dateHeure,duree,libelle) VALUES (:id,:idMatiere,:dateHeure,:duree,:libelle)");
     query.bindValue(":id",val->Getid());
     query.bindValue(":idMatiere",val->GetidMatiere());
     query.bindValue(":dateHeure",val->GetdateHeure().toString());
     query.bindValue(":duree",val->Getduree());
     query.bindValue(":libelle",val->GetlibMatiere());
     if (query.exec())
       {
           listDev.push_back(val);
           qDebug() << "Base de donnee: Insertion réussie" << endl;
       }
       else{
           qDebug() << "Base de donnee: Echec Insertion " << endl;
           qDebug() << query.lastError().text();
       }
 }

 std::vector <Classe*> Service::GetlistClassFromDB()
 {
     QSqlQuery query;
     QString listMot[3];
     QString requete="SELECT * FROM gescole.classe";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          listClass.push_back(new Classe(listMot[0],listMot[2],listMot[1].toInt()));
       }
       qDebug() << "Requette de recuperation des classes reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des classes echouee";
    }

    return listClass;
 }



 std::vector <Bulletin*> Service::GetlistBulletinFromDB()
 {
     QSqlQuery query;
     QString listMot[5];
     QString requete="SELECT * FROM gescole.Bulletin";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          Bulletin * bull= new Bulletin();
          bull->Setid(listMot[0]);
          bull->Setmoyenne(listMot[1].toFloat());
          bull->Setdecision(listMot[2]);
          bull->SetidEleve(listMot[3]);
          bull->Setrang(listMot[4].toInt());
          listBulletin.push_back(bull);
       }
       qDebug() << "Requette de recuperation des classes reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des classes echouee";
    }

    return listBulletin;
 }





 std::vector <Matiere*> Service::GetlistMatiereFromDB()
 {
     QSqlQuery query;
     QString listMot[5];
     QString requete="SELECT * FROM gescole.matiere";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          Matiere * newMat = new Matiere();
          newMat->Setid(listMot[0]);
          newMat->SetidClasse(listMot[3]);
          newMat->SetidProfesseur(listMot[2]);
          newMat->Setlibelle(listMot[1]);
          newMat->Setcoef(listMot[4].toInt());
          listMatiere.push_back(newMat);

       }
              qDebug() << "Requette de recuperation des matieres reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des matieres echouee";
    }

    return listMatiere;
 }


 std::vector <Cours*> Service::GetlistCoursFromDB()
 {
     QSqlQuery query;
     QString listMot[4];
     QString requete="SELECT * FROM gescole.cours";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          Cours * newCours = new Cours();
          newCours->Setid(listMot[0]);
          newCours->SetidMatiere(listMot[1]);
          newCours->SetDateHeure(QDateTime::fromString(listMot[2]));
          newCours->Setduree(listMot[3].toInt());
          for(int i=0;i<listMatiere.size();i++)
          {
              if(newCours->GetidMatiere()==listMatiere[i]->Getid())
              {
                  newCours->SetlibMatiere(listMatiere[i]->Getlibelle());
              }
          }
          listCours.push_back(newCours);
       }
              qDebug() << "Requette de recuperation des cours reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des cours echouee";
    }

    return listCours;

 }



 std::vector <Devoir*> Service::GetlistDevoirFromDB()
 {
     QSqlQuery query;
     QString listMot[5];
     QString requete="SELECT * FROM gescole.Devoir";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          Devoir * newDev = new Devoir();
          newDev->Setid(listMot[0]);
          newDev->SetidMatiere(listMot[1]);
          newDev->SetdateHeure(QDateTime::fromString(listMot[2]));
          newDev->SetlibMatiere(listMot[3]);
          newDev->Setduree(listMot[4].toInt());
          listDev.push_back(newDev);
       }
              qDebug() << "Requette de recuperation des devoirs reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des devoirs echouee";
    }

    return listDev;

 }

 std::vector <Enseignant*> Service::GetlistEnsFromDB()
 {
     QSqlQuery query;
     QString listMot[8];
     QString requete="SELECT * FROM gescole.enseignant";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
            }
          Enseignant * newEns = new Enseignant();
          newEns->Setid(listMot[0]);
          newEns->Setnom(listMot[1]);
          newEns->Setprenom(listMot[2]);
          newEns->Setage(listMot[3].toInt());
          newEns->Setsexe(listMot[4]);
          newEns->Setlogin(listMot[5]);
          newEns->Setpassword(listMot[6]);
          newEns->Setcontact(listMot[7]);
          listEns.push_back(newEns);

       }
       qDebug() << "Requette de recuperation des enseignants reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des enseignants echouee";
    }

    return listEns;

 }
 std::vector <Candidat*> Service::GetlistCandtFromDB()
 {
     QSqlQuery query;
     QString listMot[8];
     QString requete="SELECT * FROM gescole.candidat";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          Candidat * newCandt = new Candidat();
          newCandt->Setid(listMot[0]);
          newCandt->Setnom(listMot[1]);
          newCandt->Setprenom(listMot[2]);
          newCandt->Setage(listMot[3].toInt());
          newCandt->Setsexe(listMot[4]);
          newCandt->Setlogin(listMot[5]);
          newCandt->Setpassword(listMot[6]);
          newCandt->Setcontact(listMot[7]);
          listCandt.push_back(newCandt);

       }
       qDebug() << "Requette de recuperation des candidat reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des candidat echouee";
    }

    return listCandt;

 }

 std::vector <Candidature*> Service::GetlistCandidatureFromDB()
 {
     QSqlQuery query;
     QString listMot[5];
     QString requete="SELECT * FROM gescole.candidature";
    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          Candidature * newCand = new Candidature();
          newCand->Setid(listMot[0]);
          newCand->SetidClasse(listMot[1]);
          newCand->SetidProfesseur(listMot[2]);
          newCand->SetstatutAccepte(listMot[3]);
          newCand->SetstatutClose(listMot[4]);
          std::vector <Document*> lstDoc;
          for(int i=0;i<listDocument.size();i++)
          {
              if(listDocument[i]->GetidCandidature()==newCand->Getid())
              {
                  lstDoc.push_back(listDocument[i]);
              }
          }
          newCand->SetlisteDocument(lstDoc);

          std::vector <Commentaire*> lstCmt;
          for(int i=0;i<listComt.size();i++)
          {
              if(listComt[i]->GetidCandidature()==newCand->Getid())
              {
                  lstCmt.push_back(listComt[i]);
              }
          }
          newCand->Setcommentaires(lstCmt);

          listCandidature.push_back(newCand);

       }
       qDebug() << "Requette de recuperation des candidatures reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des candidatures echouee";
    }
    return listCandidature;
 }


 std::vector <Eleve*> Service::GetlistElevFromDB()
 {
     QSqlQuery query;
     QString listMot[10];
     QString requete="SELECT * FROM gescole.eleve";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
            }

          Eleve * newEleve = new Eleve();
          newEleve->Setid(listMot[0]);
          newEleve->Setnom(listMot[1]);
          newEleve->Setprenom(listMot[2]);
          newEleve->Setage(listMot[3].toInt());
          newEleve->Setsexe(listMot[4]);
          newEleve->Setlogin(listMot[5]);
          newEleve->Setpassword(listMot[6]);
          newEleve->SetidClasse(listMot[7]);
          newEleve->Setcontact(listMot[8]);
          listElev.push_back(newEleve);
       }
       qDebug() << "Requette de recuperation des eleves reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des eleves echouee";
    }
    return listElev;

 }
 std::vector <Document*> Service::GetlistDocumentFromDB()
 {
     QSqlQuery query;
     QString listMot[4];
     QString requete="SELECT * FROM gescole.Document";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          Document * newDoc = new Document();
          newDoc->Setid(listMot[0]);
          newDoc->Setlibelle(listMot[1]);
          newDoc->Seturl(listMot[2]);
          newDoc->SetidCandidature(listMot[3]);
          listDocument.push_back(newDoc);
       }
       qDebug() << "Requette de recuperation des documents reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des documents echouee";
    }
    return listDocument;

 }

 std::vector <Commentaire*> Service::GetlistCommentaireFromDB()
 {
     QSqlQuery query;
     QString listMot[5];
     QString requete="SELECT * FROM gescole.commentaire";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          Commentaire * newCmt = new Commentaire();
          newCmt->Setid(listMot[0]);
          newCmt->Settext(listMot[1]);
          newCmt->Setdate(listMot[2]);
          newCmt->SetidAuteur(listMot[3]);
          newCmt->SetidCandidature(listMot[4]);
          listComt.push_back(newCmt);
       }
       qDebug() << "Requette de recuperation des commentaire reussie";
    }
    else
    {
        qDebug() << "Requette de recuperation des commentaire echouee";
    }
    return listComt;

 }


 std::vector <Note*> Service::GetlistNoteFromDB()
 {
     QSqlQuery query;
     QString listMot[6];
     QString requete="SELECT * FROM gescole.note";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
              Note * newnote = new Note();
              newnote->Setid(listMot[0]);
              newnote->SetidMatiere(listMot[1]);
              newnote->Setnote(listMot[2].toFloat());
              newnote->Setcoef(listMot[3].toInt());
              newnote->SetidEleve(listMot[4]);
              newnote->Setintitule(listMot[5]);
              listNote.push_back(newnote);
            qDebug() << "Requette de recuperation des notes reussie";

       }

    }
    else
    {
        qDebug() << "Requette de recuperation des notes echouee";
    }

    return listNote;

 }



 std::vector <Matiere*> Service::GetlistMatiereFromDBforEns()
 {
     QSqlQuery query;
     QString listMot[5];
     QString requete="SELECT * FROM gescole.matiere";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          if(listMot[2]==utilisateurCourant->Getid())
          {
              qDebug() << listMot[2];
              Matiere * newMat = new Matiere();
              newMat->Setid(listMot[0]);
              newMat->SetidClasse(listMot[3]);
              newMat->SetidProfesseur(listMot[2]);
              newMat->Setlibelle(listMot[1]);
              newMat->Setcoef(listMot[4].toInt());
              listMatiere.push_back(newMat);
            qDebug() << "Requette de recuperation des matieres reussie";
          }

       }

    }
    else
    {
        qDebug() << "Requette de recuperation des matieres echouee";
    }

    return listMatiere;

 }

 std::vector <Matiere*> Service::GetlistMatiereFromDBforElev()
 {
     QSqlQuery query;
     QString listMot[5];
     QString requete="SELECT * FROM gescole.matiere";

    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          if(listMot[3]==utilisateurEleve->GetidClasse())
          {
              Matiere * newMat = new Matiere();
              newMat->Setid(listMot[0]);
              newMat->SetidClasse(listMot[3]);
              newMat->SetidProfesseur(listMot[2]);
              newMat->Setlibelle(listMot[1]);
              newMat->Setcoef(listMot[4].toInt());
              listMatiere.push_back(newMat);
            qDebug() << "Requette de recuperation des matieres reussie";
          }

       }

    }
    else
    {
        qDebug() << "Requette de recuperation des matieres echouee";
    }

    return listMatiere;

 }

 std::vector <Candidature*> Service::GetlistCandidatureFromDBforEns()
 {
     QSqlQuery query;
     QString listMot[5];
     QString requete="SELECT * FROM gescole.candidature";
    if(query.exec(requete))
    {
       while ( query.next() )
       {
          for(int i=0;i<query.record().count();i++)
             {
              listMot[i]=query.value(i).toString();
             }
          if(utilisateurCourant->Getid()==listMot[2] && (listMot[4] != "Close"))
          {
              Candidature * newCand = new Candidature();
              newCand->Setid(listMot[0]);
              newCand->SetidClasse(listMot[1]);
              newCand->SetidProfesseur(listMot[2]);
              newCand->SetstatutAccepte(listMot[3]);
              newCand->SetstatutClose(listMot[4]);
              std::vector <Document*> lstDoc;
              for(int i=0;i<listDocument.size();i++)
              {
                  if(listDocument[i]->GetidCandidature()==newCand->Getid())
                  {
                      lstDoc.push_back(listDocument[i]);
                  }
              }
              newCand->SetlisteDocument(lstDoc);

              std::vector <Commentaire*> lstCmt;
              for(int i=0;i<listComt.size();i++)
              {
                  if(listComt[i]->GetidCandidature()==newCand->Getid())
                  {
                      lstCmt.push_back(listComt[i]);
                  }
              }
              newCand->Setcommentaires(lstCmt);

              listCandidature.push_back(newCand);

           qDebug() << "Requette de recuperation des candidatures reussie";
          }
        }
    }
    else
    {
        qDebug() << "Requette de recuperation des candidatures echouee";
    }
    return listCandidature;
 }



 std::vector <Classe*> Service::GetlistClass()
 {
    return listClass;
 }
 std::vector <Matiere*> Service::GetlistMatiere()
 {
    return listMatiere;

 }
 std::vector <Enseignant*> Service::GetlistEns()
 {
    return listEns;

 }
 std::vector <Candidat*> Service::GetlistCandt()
 {
    return listCandt;

 }

 std::vector <Candidature*> Service::GetlistCandidature()
 {

    return listCandidature;
 }


 std::vector <Eleve*> Service::GetlistElev()
 {
    return listElev;

 }
 std::vector <Document*> Service::GetlistDocument()
 {

    return listDocument;
 }

 std::vector <Commentaire*> Service::GetlistCommentaire()
 {
    return listComt;
 }
 std::vector <Cours*> Service::GetlistCours()
 {
    return listCours;
 }
 std::vector <Devoir*> Service::GetlistDevoir()
 {
    return listDev;
 }
 std::vector <Note*> Service::GetlistNote()
 {
    return listNote;
 }

 std::vector <Bulletin*> Service::GetlistBulletin()
 {
    return listBulletin;
 }

 QString Service::classement(QString moyenne,QString idClasse)
 {

 }
