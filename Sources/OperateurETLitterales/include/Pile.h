#pragma once
#include <iostream>
#include <vector>
#include "Litterale.h"
#include "PileException.h"

class Pile {

    static int nb;
    static std::vector<Litterale*> tab;

public:

    static int getNB(){return nb;}
	static Litterale* pop();
	static void clear();
	static void push(Litterale* lit);
	static void afficher();

};
