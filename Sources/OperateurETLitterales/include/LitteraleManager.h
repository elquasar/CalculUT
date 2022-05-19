#ifndef LITTERALEMANAGER_H
#define LITTERALEMANAGER_H

#include "Litterale.h"
#include "LitteraleFactory.h"
#include <vector>


class LitteraleManager {

    private :

        static LitteraleManager*        instance;
               std::vector<Litterale*>  tab;

        LitteraleManager()                                        = default;
	    LitteraleManager            (const LitteraleManager& em2) = delete;
	    ~LitteraleManager();
	    LitteraleManager& operator= (const LitteraleManager& em2) = delete;



    public :

        Litterale*               addLitterale(Litterale* L);
        void removeLitterale(Litterale* L);
        // ajouter une methode remove


        bool                     isIn(Litterale* ptr_litterale);
        // Permet de savoir si un pointeur existe dans le tab

        static LitteraleManager& giveInstance();
        static void              freeInstance();

    friend std::ostream& operator<<(std::ostream& os, const LitteraleManager& lmng);
};



#endif

