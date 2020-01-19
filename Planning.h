#ifndef PLANNING_H
#define PLANNING_H

#include <QString>
#include<vector>
#include"Cours.h"
#include"Devoir.h"

class Planning
{
    public:
        Planning();
        virtual ~Planning();

        std::vector <Cours*>  GetlisteCours() { return listeCours; }
        void SetlisteCours(std::vector <Cours*>  val) { listeCours = val; }
        void addCours(Cours*  val) { listeCours.push_back(val); }
        std::vector <Devoir*> GetlisteDevoirs() { return listeDevoirs; }
        void SetlisteDevoir(std::vector <Devoir*> val) { listeDevoirs = val; }
        void addDevoir(Devoir* val) { listeDevoirs.push_back(val); }


    protected:

    private:
        QString id;
        std::vector <Cours*> listeCours;
        std::vector <Devoir*> listeDevoirs;
};

#endif // PLANNING_H
