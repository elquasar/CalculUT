#ifndef CONTROLEUR_H_INCLUDED
#define CONTROLEUR_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

/**<Include du Controleur Exception*/
#include "ControleurException.h"

/**<Include de la Pile */

#include "../../../Sources/OperateurETLitterales/include/Pile.h"

/**<Include des Litterales */

#include "../../../Sources/OperateurETLitterales/include/Litterale.h"
#include "../../../Sources/OperateurETLitterales/include/LitteraleInt.h"
#include "../../../Sources/OperateurETLitterales/include/LitteraleReelle.h"
#include "../../../Sources/OperateurETLitterales/include/LitteraleExpr.h"
#include "../../../Sources/OperateurETLitterales/include/LitteraleAtome.h"
#include "../../../Sources/OperateurETLitterales/include/LitteraleFactory.h"

/**<Include des Operateurs */

#include "OperateurManager.h"
#include "../../../Sources/OperateurETLitterales/include/Operateurs.h"

/**<Include Variable Manager */
#include "../../../Sources/OperateurETLitterales/include/VariableManager.h"

class Controleur{

private:

    /**<La Fabrique des litterales est instancie qu'une fois afin de avoir une fabrique dedans le controleur*/
	Factory_Litterale F;

	OperateurManager OP;

    /**<Le constructeur du controleur est declare par default car le Controleur c'est un "Singleton"*/
    Controleur()=default;
    static Controleur* Controleur_;

//    /**<La methode split permet creer un vecteur qui contient tous les sous-chaines contenues dans un chainde de la forme "1 2 +", vector<string> v = {"1", "2", "+"};*/
    /**<C'est methode viens de "https://es.stackoverflow.com/questions/5/c%C3%B3mo-separar-las-palabras-que-contiene-un-string-en-c-split" et il a ete adapte*/
    std::vector<std::string> split_getline(std::string str, char limitateur);

public:

    /**<Commande realise le traitement de la chaine inserez par l'utilisateur*/
    void commande(const std::string& cde);

	/**<Executer declanche l'execution d'une chaine inserez et qui a ete traite avant*/
	void executer();

    /**<Singleton*/
    Controleur(Controleur &other) = delete;
    void operator=(const Controleur &) = delete;
    static Controleur *GetInstance();

};

#endif // CONTROLEUR_H_INCLUDED
