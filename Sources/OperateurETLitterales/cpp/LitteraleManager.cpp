#include "../include/LitteraleManager.h"


LitteraleManager* LitteraleManager::instance = nullptr;

LitteraleManager& LitteraleManager::giveInstance() {
    if (instance == nullptr) {
		instance = new LitteraleManager();
	}
	return *instance;

}

void LitteraleManager::freeInstance() {
    delete instance;
    instance = nullptr;
}

LitteraleManager::~LitteraleManager() {

    for (auto element : this->tab) {
        delete element;
    }

}


Litterale* LitteraleManager::addLitterale(Litterale* L) {
    tab.push_back(L);
    return (this->tab.back());
}

void LitteraleManager::removeLitterale(Litterale* L) {
    for (std::vector<Litterale*>::iterator it = tab.begin(); it != tab.end(); it++) {
        if ((*it) == L) {
            delete *(it);
            tab.erase(it);
            return;
        }
    }
}

bool LitteraleManager::isIn(Litterale* ptr_litterale) {

    for (auto const& pointeur : this->tab) {
        if (pointeur == ptr_litterale) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const LitteraleManager& lmng) {
    os << "CONTENU DU MANAGER :" << std::endl;
    for (auto const& ptr_litteraux : lmng.tab) {
        os << *ptr_litteraux << std::endl;
    }
    return os;
}
