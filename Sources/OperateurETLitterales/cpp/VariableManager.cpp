#include "../include/VariableManager.h"

VariableManager::VariableManager(LitteraleManager* ptr_lmng) : lmng(ptr_lmng) {}
VariableManager::~VariableManager(){}
const std::map<LitteraleAtome*, Litterale*>& VariableManager::getMap() const {return this->map;}

void VariableManager::removeAssociation(LitteraleAtome* key) {

    bool good = false;

    auto Brouillon = key;

    for  (auto myPair : map) {

        if (myPair.first->getValue() == key->getValue()) {

            Brouillon = myPair.first;

            good = true;

        }

    }

    auto Brouillon2 = getValue(Brouillon);
    map.erase(Brouillon);

    LitteraleManager::giveInstance().removeLitterale(Brouillon);
    LitteraleManager::giveInstance().removeLitterale(Brouillon2 );

    if (!good) {
        throw LitteraleException("Il n existe pas d association de ce nom");
    }
}


VariableManager& VariableManager::addAssociation(LitteraleAtome* expression,
Litterale* litterale) {

    bool isIn = false;

    for  (const auto& myPair : map) {
        if (myPair.first->getValue() == expression->getValue()) {
            isIn = true;
        }
    }

    if (isIn) {
        throw LitteraleException("Le nom de la variable est deja utilise pour une autre association");
        return *this;
    }

     // Vérifier si les deux arguments existent dans le litterale manager
    if (lmng->isIn(expression) && lmng->isIn(litterale)) {
        this->map[expression] = litterale;    }

    // Sinon, il faudra créer les variables en conséquences via le LitteraleManager

    if (lmng->isIn(expression) && !lmng->isIn(litterale)) {
        this->map[expression] = lmng->addLitterale(litterale);
    }

    if (!lmng->isIn(expression) && lmng->isIn(litterale)) {

        lmng->addLitterale(expression);
        this->map[expression] = litterale;
    }

    if (!lmng->isIn(expression) && !lmng->isIn(litterale)) {

        lmng->addLitterale(expression);
        this->map[expression] = lmng->addLitterale(litterale);
    }

    return *this;
}


std::ostream& operator<<(std::ostream& os, const VariableManager& lmng) {

    for (auto association : lmng.getMap()) {

        os << *association.first << " : " << *association.second << "\n";
    }
    return os;

}

// Imoplémentation du singleton

VariableManager* VariableManager::instance = nullptr;

VariableManager& VariableManager::giveInstance(LitteraleManager* ptr_lmng) {
	if (instance == nullptr) {
		instance = new VariableManager(ptr_lmng);
	}
	return *instance;
}

void VariableManager::freeInstance() {
	delete instance;
	instance = nullptr;
}

Litterale* VariableManager::getValue(LitteraleAtome* key) {

    if (map.find(key) != map.end()) {
        return map.find(key)->second;
    }
    else {
        throw LitteraleException("La variable n existe pas");
        return nullptr;
    }
}

Litterale* VariableManager::getValue(std::string key) {

    bool good = false;

    for  (auto myPair : map) {
        if (myPair.first->getValue() == key) {

            return myPair.second;
            good = true;
        }
    }
    if (!good) {

        throw LitteraleException("Il n existe pas d association de ce nom");

    }
    return nullptr;
}

