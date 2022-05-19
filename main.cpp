#include <iostream>

/**<Include des Opérateurs */

#include "Sources/OperateurETLitterales/include/Operateurs.h"

/**<Include du Controleur */
#include "Sources/Controleur/include/Controleur.h"

using namespace std;

int main() {

    //Test de Dorian

    auto opSwap = Swap();

    cout<<"Variable manager Contenue\n"<<VariableManager::giveInstance(&LitteraleManager::giveInstance());

    Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create("3")));
    Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create("1")));

    Pile::afficher();
    auto opSto = Sto();
    Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create("[_1_+_]")));
    Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create("'X'")));
    opSto.eval();
    cout<<"Variable manager Contenue\n"<<VariableManager::giveInstance(&LitteraleManager::giveInstance());
    opSwap.eval();
    Pile::afficher();

    //Fin des tests de Dorian

    //Instantiation du Controleur pour boucle des commandes
    //Les operations sont fait correctement, il faut ajouter STO et EVAL, après ajouter la classe litterale programme
    Controleur::GetInstance()->executer();

    return 0;
}
