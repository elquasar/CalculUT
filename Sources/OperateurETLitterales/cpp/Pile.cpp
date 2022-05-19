#include "../include/Pile.h"
#include "../include/Litterale.h"
#include "../include/LitteraleManager.h"

int Pile::nb = 0;
std::vector<Litterale*> Pile::tab = std::vector<Litterale*>();

Litterale* Pile::pop() {
	if (tab.size() == 0) {
		throw PileException("Tentative de pop sur une pile vide");
	}
	//std::cout << "nb = " << nb << std::endl;
	Litterale* truc = tab.back();
	tab.pop_back();
	nb--;
	//std::cout << "fin pop" << std::endl;
	return truc;
}

void Pile::push(Litterale* lit) {
	tab.push_back(lit);
	nb++;
}

void Pile::clear() {
	LitteraleManager& litMan = LitteraleManager::giveInstance();
	//std::cout << "Taille de la pile avant clear : " << tab.size() << std::endl;
	for (int i = tab.size() - 1; i >= 0; i--) {
		/*delete tab.at(i);*/
		litMan.removeLitterale(tab.at(i));
		tab.pop_back();
	}
	//std::cout << "Taille de la pile aprs clear : " << tab.size() << std::endl;
}

void Pile::afficher() {
	std::cout << "===PILE=== " << std::endl;
	for (int i = tab.size() - 1; i >= 0; i--) {
		std::cout << *(tab.at(i)) << std::endl;
	}
	std::cout << "==========\n\n";
}
