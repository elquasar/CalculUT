#ifndef OPERATEURMANAGER_H_INCLUDED
#define OPERATEURMANAGER_H_INCLUDED

#include "../../OperateurETLitterales/include/Operateurs.h"

using namespace std;


class OperateurManager{

    /**<Une vecteur de type "String" contient tous les op�rateur qui peuvent etre utilis�s dans la calculatrice, le fonctionnement est similaire a avoir des mots reservees dans la calculatrice, ces mots ne peuvent pas etre utilisees comme des noms de Litterales Atome ou expression, c'est interdit*/
    vector<string> Operateurs = {"+", "-", "*", "/",
    "DIV", "MOD", "NEG", "=", "!=", "=<", ">=", "<", ">", "AND",
    "OR", "NOT", "EVAL", "DUP", "DROP",
    "SWAP", "CLEAR", "IFT", "STO", "FORGET", "NUM", "DEN"};

public:

    /**<"cestunOperateur" permet identifier si l'operateur forme partie de l'ensemble des operateurs garde*/
    bool cestunOperateur(string A) const;

    void FaireOperation(const string OperateurS);

};

#endif // OPERATEURMANAGER_H_INCLUDED
