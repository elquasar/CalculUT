#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include "LitteraleAtome.h"
#include "LitteraleReelle.h"
#include "LitteraleInt.h"
#include "LitteraleRatio.h"
#include "LitteraleManager.h"
#include <string>
#include <map>

// Singleton !


class VariableManager {

    public :

        // Implémentation du singleton, méthode d'instanciation

        static VariableManager* instance;
        static VariableManager& giveInstance(LitteraleManager* ptr_lmng);
        static void             freeInstance();


        // Permet l'ajout ou la suppression d'une association.
        /*Attention : addAssociation appelle le LitteraleManager s'il doit créer de nouvelles litterales
        *             lors de la création d'une association.
        *
        *             removeAssociation ne détruit pas les litterales passés en argument mais seulement
        *             les liens entre eux au sein de la map.
        */

        VariableManager& addAssociation   (LitteraleAtome* expression, Litterale* litterale);
        void             removeAssociation(LitteraleAtome* expression);

        // Ce getteur permet uniquement l'accès au tableau en lecture seule par l'utilisateur,
        // la modification se fait uniquement via les méthodes de la classe VariableManager.

        const std::map<LitteraleAtome*, Litterale*>& getMap  () const;
        Litterale*                                   getValue(LitteraleAtome* key);
        Litterale*                                   getValue(std::string key);

    private :

        // Contructeur et destructeurs en privée
        // Constructeur de recopie supprimé, opérateur d'affectation supprimé

        VariableManager            (LitteraleManager* ptr_lmng);
        ~VariableManager();
        VariableManager            (const VariableManager& em2) = delete;
        VariableManager& operator= (const VariableManager& em2) = delete;

        // Attributs de VariableManager

        LitteraleManager*                          lmng;
        std::map<LitteraleAtome*, Litterale*> map;

        /*Le Variable Manager dispose d'un pointeur sur le Litterale Manager
        * car ce n'est pas lui qui est reponsable de la création des litterales
        * il s'occupe uniquement de créer les liens entre les litterales (existantes
        * ou non). Si besoin il peut appeler LitteraleManager pour instancier des litterales.
        * */
};

/*Opérateur d'affichage pour le debuggage*/
std::ostream& operator<<(std::ostream& os, const VariableManager& lmng);

#endif
