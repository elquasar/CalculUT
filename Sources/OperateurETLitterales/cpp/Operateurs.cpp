#include "../include/Operateurs.h"
#include <iostream>
#include "../include/Pile.h"
#include "../include/LitteraleFactory.h"
#include "../../Controleur/include/Controleur.h"
#include "../include/VariableManager.h"
#include "../include/OperateursException.h"
#include "../include/PileException.h"

#include <iostream>
#include <vector>

void Operateur::eval() const{
	std::vector<Litterale*> params = std::vector<Litterale*>();
	int i = 0;
	try{
		for (i = 0; i < getArite(); i++) {
			params.push_back(Pile::pop());
		}
	}catch(PileException& e){
		for (int j = 0; j < params.size(); j++) {
			LitteraleManager::giveInstance().removeLitterale(params.at(i));
		}
		throw OperateursException("L'operation requiert " + std::to_string(getArite()) + " operandes ; " + std::to_string(i) + " recue(s)");
	}
	try {
		exec(params);
	}
	catch (OperateursException e) {
		//En cas d'erreur, on supprime les litterales depiles avant de relancer l'exception (pour l'appelant)
		for (int i = 0; i < getArite(); i++) {
			LitteraleManager::giveInstance().removeLitterale(params.at(i));
		}
		throw OperateursException(e);
	}
	finDepilage(params);
}

void Operateur::finDepilage(std::vector<Litterale*> operandes) const{
	for (int i = 0; i < getArite(); i++) {
		LitteraleManager::giveInstance().removeLitterale(operandes.at(i));
	}
}

void Add::exec(std::vector<Litterale*> operandes) const{
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		auto rat1 = dynamic_cast<LitteraleRatio*>(ree1);
		auto rat2 = dynamic_cast<LitteraleRatio*>(ree2);
		if (rat1 != nullptr && rat2!=nullptr) {
			//RATIONNEL
			//les deux oprandes sont rationnelles : on attend un rationnel en rsultat
			//std::cout << res << std::endl;		//dcommenter pour vrif valeur avant push
			LitteraleRatio* lit = new LitteraleRatio(*rat1 + *rat2);
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}/*
		else if (rat1 != nullptr) {
			//REEL
			//au moins une des oprandes est un rel : on attend donc un rel en rsultat
			//on appellera ainsi LitteraleReelle.operator+ et pas LitteraleRatio.operator+
			//la premire oprande est un rationnel, l'autre un rel
			Pile::push(new LitteraleReelle(*rat2 + *rat1));
		} */
		else {
			LitteraleReelle* lit = new LitteraleReelle(*ree1 + *ree2);
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}

	}
	else {
		//La littrale n'est pas numrique => throw exception
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void Sub::exec(std::vector<Litterale*> operandes) const{
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		auto rat1 = dynamic_cast<LitteraleRatio*>(ree1);
		auto rat2 = dynamic_cast<LitteraleRatio*>(ree2);
		if (rat1 != nullptr && rat2 != nullptr) {
			//RATIONNEL
			//les deux oprandes sont rationnelles : on attend un rationnel en rsultat
			//std::cout << res << std::endl;		//dcommenter pour vrif valeur avant push
			LitteraleRatio* lit = new LitteraleRatio(*rat1 - *rat2);
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}/*
		else if (rat1 != nullptr) {
			Pile::push(new LitteraleReelle(*rat2 - *rat1));
		}*/
		else {
			//REEL
			//au moins une des oprandes est un rel : on attend donc un rel en rsultat
			LitteraleReelle* lit = new LitteraleReelle(*ree1 - *ree2);
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void Mul::exec(std::vector<Litterale*> operandes) const{
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		auto rat1 = dynamic_cast<LitteraleRatio*>(ree1);
		auto rat2 = dynamic_cast<LitteraleRatio*>(ree2);
		if (rat1 != nullptr && rat2 != nullptr) {
			//RATIONNEL
			//les deux oprandes sont rationnelles : on attend un rationnel en rsultat
			//std::cout << res << std::endl;		//dcommenter pour vrif valeur avant push
			LitteraleRatio* lit = new LitteraleRatio(*rat1 * *rat2);
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}
		else {
			//REEL
			//au moins une des oprandes est un rel : on attend donc un rel en rsultat
			LitteraleReelle* lit = new LitteraleReelle(*ree1 * *ree2);
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}

		//l'opration renvoie un objet, or on a besoin d'un pointeur pour la pile
		//problme : en fin de bloc, res est supprim, et donc le pointeur dans la pile ne pointe plus sur rien :(
		//=> d'o l'utilis d'un LitteraleManager peut-tre?
		//a permettrait de garder la main sur le cycle de vie des littrales en les stockant dedans => pas supprims en fin de bloc


	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void Div::exec(std::vector<Litterale*> operandes) const{
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		auto rat1 = dynamic_cast<LitteraleRatio*>(ree1);
		auto rat2 = dynamic_cast<LitteraleRatio*>(ree2);

		if (rat1 != nullptr && rat2 != nullptr) {
			//RESULTAT RATIONNEL
			if (rat2->getNum() != 0) {
				//ok
				LitteraleRatio* lit = new LitteraleRatio(*rat1 / *rat2);
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
			else {
				throw OperateursException("Division par zero");
			}
		}
		else {
			//RESULTAT REEL
			if (ree2->getValue()!=0) {
				//ok
				LitteraleReelle* lit = new LitteraleReelle(*ree1 / *ree2);
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
			else {
				throw OperateursException("Division par zero");
			}
		}
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void DivEntiere::exec(std::vector<Litterale*> operandes) const{
	auto int1 = dynamic_cast<LitteraleInt*>(operandes.at(1));
	auto int2 = dynamic_cast<LitteraleInt*>(operandes.at(0));

	if (int1 != nullptr && int2 != nullptr) {
		if (int2->getNum() != 0) {
			int val = (*int1 / *int2).getValue();
			LitteraleInt* lit = new LitteraleInt(val);
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}
		else {
			throw OperateursException("Division par zero");
		}
	}
	else {
		throw OperateursException("La litterale n'est pas un entier");
	}
}

void Mod::exec(std::vector<Litterale*> operandes) const{
	auto int1 = dynamic_cast<LitteraleInt*>(operandes.at(1));
	auto int2 = dynamic_cast<LitteraleInt*>(operandes.at(0));

	if (int1 != nullptr && int2 != nullptr) {
		if (int2->getNum() != 0) {
			int val = (*int1 / *int2).getValue();
			if (val < 0) {
				val = int2->getNum() - val;
			}
			LitteraleInt* lit = new LitteraleInt(int1->getNum()-(int2->getNum()*val));
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}
		else {
			throw OperateursException("Division par zero");
		}
	}
	else {
		throw OperateursException("La litterale n'est pas un entier");
	}
}

void Neg::exec(std::vector<Litterale*> operandes) const{
	auto ree = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree != nullptr) {
		auto rat = dynamic_cast<LitteraleRatio*>(ree);
		if (rat != nullptr) {
			if (rat->getDen() == 1) {
				//ENTIER
				LitteraleInt* lit = new LitteraleInt(-rat->getNum());
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
			else {
				//RATIONNEL
				LitteraleRatio* lit = new LitteraleRatio(-rat->getNum(), rat->getDen());
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
		}
		else {
			//REEL
			LitteraleReelle* lit = new LitteraleReelle(-rat->getValue());
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void Eq::exec(std::vector<Litterale*> operandes) const {
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		bool res = false;
		auto rat1 = dynamic_cast<LitteraleRatio*>(operandes.at(1));
		auto rat2 = dynamic_cast<LitteraleRatio*>(operandes.at(0));
		if (rat1 != nullptr && rat2 != nullptr) {
			res = *rat1 == *rat2;
		}
		else {
			res = *ree1 == *ree2;
		}

		LitteraleInt* lit = new LitteraleInt(res ? 1 : 0);	//1 si vrai, 0 si faux
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void NotEq::exec(std::vector<Litterale*> operandes) const {
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		bool res = false;
		auto rat1 = dynamic_cast<LitteraleRatio*>(operandes.at(1));
		auto rat2 = dynamic_cast<LitteraleRatio*>(operandes.at(0));
		if (rat1 != nullptr && rat2 != nullptr) {
			res = *rat1 != *rat2;
		}
		else {
			res = *ree1 != *ree2;
		}

		LitteraleInt* lit = new LitteraleInt(res ? 1 : 0);	//1 si vrai, 0 si faux
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void InfEq::exec(std::vector<Litterale*> operandes) const {
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		bool res = false;
		auto rat1 = dynamic_cast<LitteraleRatio*>(operandes.at(1));
		auto rat2 = dynamic_cast<LitteraleRatio*>(operandes.at(0));
		if (rat1 != nullptr && rat2 != nullptr) {
			res = *rat1 <= *rat2;
		}
		else {
			res = *ree1 <= *ree2;
		}

		LitteraleInt* lit = new LitteraleInt(res ? 1 : 0);	//1 si vrai, 0 si faux
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}


void SupEq::exec(std::vector<Litterale*> operandes) const {
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		bool res = false;
		auto rat1 = dynamic_cast<LitteraleRatio*>(operandes.at(1));
		auto rat2 = dynamic_cast<LitteraleRatio*>(operandes.at(0));
		if (rat1 != nullptr && rat2 != nullptr) {
			res = *rat1 >= *rat2;
		}
		else {
			res = *ree1 >= *ree2;
		}

		LitteraleInt* lit = new LitteraleInt(res ? 1 : 0);	//1 si vrai, 0 si faux
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void Inf::exec(std::vector<Litterale*> operandes) const {
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		bool res = false;
		auto rat1 = dynamic_cast<LitteraleRatio*>(operandes.at(1));
		auto rat2 = dynamic_cast<LitteraleRatio*>(operandes.at(0));
		if (rat1 != nullptr && rat2 != nullptr) {
			res = *rat1 < *rat2;
		}
		else {
			res = *ree1 < *ree2;
		}

		LitteraleInt* lit = new LitteraleInt(res ? 1 : 0);	//1 si vrai, 0 si faux
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}

void Sup::exec(std::vector<Litterale*> operandes) const {
	auto ree1 = dynamic_cast<LitteraleReelle*>(operandes.at(1));
	auto ree2 = dynamic_cast<LitteraleReelle*>(operandes.at(0));

	if (ree1 != nullptr && ree2 != nullptr) {
		bool res = false;
		auto rat1 = dynamic_cast<LitteraleRatio*>(operandes.at(1));
		auto rat2 = dynamic_cast<LitteraleRatio*>(operandes.at(0));
		if (rat1 != nullptr && rat2 != nullptr) {
			res = *rat1 > *rat2;
		}
		else {
			res = *ree1 > *ree2;
		}

		LitteraleInt* lit = new LitteraleInt(res ? 1 : 0);	//1 si vrai, 0 si faux
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un nombre");
	}
}


//TODO : redef operator> ?

void And::exec(std::vector<Litterale*> operandes) const {
	auto int1 = dynamic_cast<LitteraleInt*>(operandes.at(1));
	auto int2 = dynamic_cast<LitteraleInt*>(operandes.at(0));

	if (int1 != nullptr && int2 != nullptr) {
		LitteraleInt* lit = new LitteraleInt((int1->getNum() != 0 && int2->getNum() != 0)?1:0);
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un entier");
	}
}

void Or::exec(std::vector<Litterale*> operandes) const {
	auto int1 = dynamic_cast<LitteraleInt*>(operandes.at(1));
	auto int2 = dynamic_cast<LitteraleInt*>(operandes.at(0));

	if (int1 != nullptr && int2 != nullptr) {
		LitteraleInt* lit = new LitteraleInt((int1->getNum() || int2->getNum() != 0) ? 1 : 0);
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un entier");
	}
}

void Not::exec(std::vector<Litterale*> operandes) const {
	auto val = dynamic_cast<LitteraleInt*>(operandes.at(0));

	if (val != nullptr) {
		LitteraleInt* lit = new LitteraleInt((val->getNum() != 0)? 0 : 1);
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("La litterale n'est pas un entier");
	}
}


void Dup::finDepilage(std::vector<Litterale*> operandes) const
{
	//On ne supprime pas la littrale qu'on vient de dupliquer!
	return;
}

void Dup::exec(std::vector<Litterale*> operandes) const
{
	//On remet la litterale a dupliquer dans la pile (elle a t dpile prcdemment)
	Pile::push(operandes.at(0));
	auto ree = dynamic_cast<LitteraleReelle*>(operandes.at(0));
	if (ree != nullptr) {
		auto rat = dynamic_cast<LitteraleRatio*>(operandes.at(0));
		if (rat != nullptr) {
			auto ent = dynamic_cast<LitteraleInt*>(operandes.at(0));
			if (ent != nullptr) {
				//entier
				LitteraleInt* lit = new LitteraleInt(ent->getValue());
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
			else {
				//rationel
				LitteraleRatio* lit = new LitteraleRatio(rat->getNum(), rat->getDen());
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
		}
		else {
			//reel
			LitteraleReelle* lit = new LitteraleReelle(ree->getValue());
			LitteraleManager::giveInstance().addLitterale(lit);
			Pile::push(lit);
		}
	}
	else {
		auto ato = dynamic_cast<LitteraleAtome*>(operandes.at(0));
		if (ato != nullptr) {
			auto exp = dynamic_cast<LitteraleExpression*>(operandes.at(0));
			if (exp != nullptr) {
				//expression
				LitteraleExpression* lit = new LitteraleExpression(exp->getValue());
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
			else {
				//atome
				LitteraleAtome* lit = new LitteraleAtome(ato->getValue());
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
		}
		else {
			auto prog = dynamic_cast<LitteraleProgramme*>(operandes.at(0));
			if (prog != nullptr) {
				//programme
				LitteraleProgramme* lit = new LitteraleProgramme(prog->getValue());
				LitteraleManager::giveInstance().addLitterale(lit);
				Pile::push(lit);
			}
			else {
				//rien du tout... bizarre..?
				throw OperateursException("Type de litterale inconnu... Comment on en est arrives la?");
			}
		}
	}
}

void Drop::exec(std::vector<Litterale*> operandes) const
{
	//une littrale a dj t dpile, aucune autre action n'est ncessaire
}


void Swap::finDepilage(std::vector<Litterale*> operandes) const {
	//On ne supprime pas les littrales car on change simplement leur position dans la pile
	return;
}

void Swap::exec(std::vector<Litterale*> operandes) const
{
	Pile::push(operandes.at(0));
	Pile::push(operandes.at(1));
}

void Clear::exec(std::vector<Litterale*> operandes) const
{
	Pile::clear();
}

void Eval::exec(std::vector<Litterale*> operandes) const {
	//std::cout<<"Avant"<<std::endl;
	auto prog = dynamic_cast<LitteraleProgramme*>(operandes.at(0));
	//std::cout<<"Apres"<<std::endl;
	if (prog != nullptr) {
        //std::cout<<"Programme"<<std::endl;
		std::string strProg = prog->getValue();
		//On supprime les crochets au dbut et  la fin de la littrale programme pour l'valuation
		strProg.erase(0, 1);
		strProg.erase(strProg.size()-1, 1);

		//std::cout<<strProg<<std::endl;

		std::string Temp;

        /**<Console Version*/
        for(char t: strProg){

            if( t == ' ' ) Temp = Temp + '_';
            else Temp = Temp + t;

        }

		try {

		    //std::cout<<Temp<<std::endl;
			Controleur::GetInstance()->commande(Temp);
		}
		catch (ControleurException& e) {
			throw OperateursException("Erreur lors de l'evaluation du programme");
		}
	}
	else {
		auto exp = dynamic_cast<LitteraleExpression*>(operandes.at(0));
		if (exp != nullptr) {
			//La littrale est une expression
			//=> on rechercher une variable correspondant  l'atome contenu dans l'expression
			try {
				try {

				    using namespace std;

                    streambuf* oldCoutStream = cout.rdbuf();
                    ostringstream strCout;
                    cout.rdbuf(strCout.rdbuf());
                    cout << *exp;
                    cout.rdbuf(oldCoutStream);

                    string ExpressionValue = strCout.str();

                    ExpressionValue.erase(0, 1);
                    ExpressionValue.erase(ExpressionValue.size()-1, 1);

					//On instancie une nouvelle littrale prenant pour valeur celle de la variable
					Litterale* lit = VariableManager::giveInstance(&LitteraleManager::giveInstance()).getValue(ExpressionValue);
					LitteraleManager::giveInstance().addLitterale(lit);

					string A = ExpressionValue;

					ExpressionValue = "";

					{

                    streambuf* oldCoutStream = cout.rdbuf();
                    ostringstream strCout;
                    cout.rdbuf(strCout.rdbuf());
                    cout << *lit;
                    cout.rdbuf(oldCoutStream);

                    string ExpressionValue = strCout.str();

                    if( ExpressionValue[0] == '['){

                        ExpressionValue.erase(0, 1);
                        ExpressionValue.erase(ExpressionValue.size()-1, 1);

                    }

                    std::string Temp;

                    /**<Console Version*/
                    for(char t: ExpressionValue){

                        if( t == ' ' ) Temp = Temp + '_';
                        else Temp = Temp + t;

                    }



					//Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create(ExpressionValue)));
                        Controleur::GetInstance()->commande(Temp);

					}
                    /*
                    auto opEval = Eval();
                    opEval.eval();
                    */

				}
				catch (LitteraleException& e) {
					throw OperateursException("La litterale atome evaluee ne correspond a aucune variable");
				}
			}
			catch (LitteraleException e) {
				Litterale* lit = VariableManager::giveInstance(&LitteraleManager::giveInstance()).getValue(exp);
			}

		}
		else {
			throw OperateursException("Une litterale programme ou expression est attendue en parametre");
		}
	}
}

void Ift::exec(std::vector<Litterale*> operandes) const {
	auto cond = dynamic_cast<LitteraleInt*>(operandes.at(1));
	if (cond != nullptr) {
		if (cond->getNum() != 0) {
			//On ne procde  l'valuation du second paramtre que si le premier est un entier diffrent de 0
			auto prog = dynamic_cast<LitteraleProgramme*>(operandes.at(0));
			if (prog != nullptr) {
				std::string strProg = prog->getValue();
				//On supprime les crochets au dbut et  la fin de la littrale programme pour l'valuation
				strProg.erase(0, 1);
				strProg.erase(strProg.size() - 1, 1);

                //std::cout<<strProg<<std::endl;

                std::string Temp;

                /**<Console Version*/
                for(char t: strProg){

                    if( t == ' ' ) Temp = Temp + '_';
                    else Temp = Temp + t;

                }

                try {

                    //std::cout<<Temp<<std::endl;
                    Controleur::GetInstance()->commande(Temp);


                            //Controleur::GetInstance()->commande(strProg);
                }
                catch (ControleurException& e) {
                    throw OperateursException("Erreur lors de l'evaluation du programme");
                }

			}
			else {
				auto exp = dynamic_cast<LitteraleExpression*>(operandes.at(0));
				if (exp != nullptr) {
					//La littrale est une expression
					//=> on rechercher une variable correspondant  l'atome contenu dans l'expression
					try {
						try {
							//On instancie une nouvelle littrale prenant pour valeur celle de la variable
							Litterale* lit = VariableManager::giveInstance(&LitteraleManager::giveInstance()).getValue(exp);
							LitteraleManager::giveInstance().addLitterale(lit);
							Pile::push(lit);
						}
						catch (LitteraleException& e) {
							throw OperateursException("La litterale atome evaluee ne correspond a aucune variable");
						}
					}
					catch (LitteraleException e) {
						Litterale* lit = VariableManager::giveInstance(&LitteraleManager::giveInstance()).getValue(exp);
					}

				}
				else {
					throw OperateursException("Une litterale programme ou expression est attendue en second parametre");
				}
			}
		}
	}
	else {
		throw OperateursException("Une litterale entiere est attendue en premiere operande");
	}
}

void Sto::finDepilage(std::vector<Litterale*> operandes) const
{
	//On ne supprime pas les littrales car on doit pouvoir les retrouver dans le VariableManager
	return;
}

void Sto::exec(std::vector<Litterale*> operandes) const {
	auto exp = dynamic_cast<LitteraleExpression*>(operandes.at(0));
	if (exp != nullptr) {
		VariableManager::giveInstance(&LitteraleManager::giveInstance()).addAssociation(exp, operandes.at(1));
	}
	else {
		throw OperateursException("Une litterale expression est attendue en second parametre");
	}

}

void Forget::exec(std::vector<Litterale*> operandes) const {
	auto ato = dynamic_cast<LitteraleAtome*>(operandes.at(0));
	if (ato != nullptr) {
		try {
			//On supprime la littrale stocke dans le variable manager
			VariableManager::giveInstance(&LitteraleManager::giveInstance()).removeAssociation(ato);

		}
		catch (LitteraleException e) {
			throw OperateursException("Aucune variable n'est associe  l'atome reu en paramtre");
		}
	}
	else {
		throw OperateursException("Une litterale atome est attendue");
	}

}

void Num::exec(std::vector<Litterale*> operandes) const {
	auto rat = dynamic_cast<LitteraleRatio*>(operandes.at(0));

	if (rat != nullptr) {
		LitteraleInt* lit = new LitteraleInt(rat->getNum());
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("Une litterale rationnelle est attendue");
	}
}

void Den::exec(std::vector<Litterale*> operandes) const {
	auto rat = dynamic_cast<LitteraleRatio*>(operandes.at(0));

	if (rat != nullptr) {
		LitteraleInt* lit = new LitteraleInt(rat->getDen());
		LitteraleManager::giveInstance().addLitterale(lit);
		Pile::push(lit);
	}
	else {
		throw OperateursException("Une litterale rationnelle est attendue");
	}
}
