#include "../include/Controleur.h"

using namespace std;

Controleur* Controleur::Controleur_= nullptr;;

/**<Instantiation du Controleur Singlenton*/
Controleur* Controleur::GetInstance(){

    if(Controleur_==nullptr){

        Controleur_ = new Controleur();

    }

    return Controleur_;
}

vector<string> Controleur::split_getline(string str, char limitateur){

    /**<Separation des espaces de la chainde caracteres pour le traitement, le resultat est stocke dans un vecteur du type string, compose des chaines extraites*/
    vector<string> resultat;
    istringstream isstream(str);
    string mot;

    while(getline(isstream, mot, limitateur)){

        if( 0 < mot.size() )resultat.push_back(mot);
    }

    return resultat;
}

void Controleur::commande(const string& cde) {

    vector<string> A;

    char separateur = '_';

    /**<Separation de la chaine en differentes elements d'un vecteur du type string*/
    //Changer '_' pour ' ' pour l'interface
    A = split_getline(cde, separateur);

    /**<Chaine pour la creation d'une litterale programme, si c'est le cas*/
    string LitteraleProgramme = "";
    int LitProg = 0;

    /**<On parocourit les differentes elements de la commande a fin d'identifier le tipe de litterale ou operateur*/

    int i = 0;

    int DuplicateProgramme = 0;

    for (string TemporalString : A) {

        /**<On utilise des differentes identificateur des expressions regulieres pour les litterales suivantes*/

        /**<Expression Reguliere Litterale Rational*/
        regex RegexRational("[0-9]+/[0-9]+");
        /**<Expression Reguliere Litterale Entier*/
        regex RegexEntier("[0-9]+");
        /**<Expression Reguliere Litterale Reel*/
        regex RegexReel("^[-]?[0-9]*[.][0-9]+$");

        /**<Expression Reguliere Litterale Atome*/
        regex RegexAtome("[A-Z]+([0-9]*[A-Z]*)*([A-Z]*[0-9]*)");
        /**<Expression Reguliere Litterale Expression*/
        regex RegexExpression("'[A-Z]+([0-9]*[A-Z]*)*([A-Z]*[0-9]*)'");

        if( TemporalString == "[" || LitProg == 1 ){

            if( TemporalString == "[" )DuplicateProgramme++;
            if( TemporalString == "]" )DuplicateProgramme--;

            LitProg = 1;

            LitteraleProgramme = LitteraleProgramme + " " + TemporalString;

            if( TemporalString == "]" && DuplicateProgramme == 0){

                    LitProg = 0;

                    string A;

                    for( size_t a = 1; a < LitteraleProgramme.size(); a++){

                        A = A + LitteraleProgramme[a];

                    }

                    Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create(A)));

            }

        }else{

            if( regex_match(TemporalString.begin(), TemporalString.end(), RegexAtome) && !OP.cestunOperateur( TemporalString ) ){

                //cout <<"Litterale Atome"<<endl;

                bool suivante = false;

                if( i < A.size()-1 ){

                    int j = 0;

                    string C;

                    for (string B : A) {

                        if( j == i+1 ) C = B;

                        j++;

                    }

                   if ( C == "FORGET" ){

                    suivante = true;

                    Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create(TemporalString)));

                   }
                }else{

                    auto A = VariableManager::giveInstance(&LitteraleManager::giveInstance()).getValue(TemporalString);

                    //cout<<"->"<<A<<"<-"<<endl;

                    if( VariableManager::giveInstance(&LitteraleManager::giveInstance()).getValue(TemporalString) ){

                        //cout<<"->"<<TemporalString<<"<-"<<endl;

                        TemporalString = "'"+ TemporalString +"'";
                        //cout<<"->"<<TemporalString<<"<-"<<endl;
                        TemporalString = TemporalString + separateur +"EVAL";
                        //cout<<"->"<<TemporalString<<"<-"<<endl;

                        commande( TemporalString );

                        //delete TempLit;

                    }

                }



            }else if( regex_match(TemporalString.begin(), TemporalString.end(), RegexExpression) ){

                        //cout <<"Litterale Expression"<<endl;

                        TemporalString.erase(0, 1);
                        TemporalString.erase(TemporalString.size() - 1, 1);

                        if( OP.cestunOperateur( TemporalString ) ){

                            throw ControleurException("L'expression inserez est une mot reservee");

                        }

                        TemporalString = "'"+ TemporalString +"'";
                        //Empiler, pour STO
                        Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create(TemporalString)));

                }else if( regex_match(TemporalString.begin(), TemporalString.end(), RegexRational) ){

                        //cout <<"Litterale Rational"<<endl;
                        Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create(TemporalString)));

                    }else if( regex_match(TemporalString.begin(), TemporalString.end(), RegexEntier) ){

                        //cout <<"Litterale Entier"<<endl;
                        Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create(TemporalString)));

                        }else if( regex_match(TemporalString.begin(), TemporalString.end(), RegexReel) ){

                            //cout <<"Litterale Reel"<<endl;
                            Pile::push(LitteraleManager::giveInstance().addLitterale(Factory_Litterale::create(TemporalString)));

                        }else if( OP.cestunOperateur( TemporalString )){

                                //cout <<"Operateur"<<endl;

                                OP.FaireOperation(TemporalString);

                            }else{

                                    throw ControleurException("Le texte introduit ne correspond pas a aucune litterale ou operateur");

                                }

        }

    i++;

    }

    cin.clear();

}

void Controleur::executer() {

    /**<Methode executer du TD, pour tester la calculatrice dans la console*/

	string s;
	cout << "Veuillez saisir une valeur ou q pour arreter: ";
	cin.clear();
	getline(cin, s);

	cin.clear();

	while (s != "q") {

        try{

            commande(s);

            Pile::afficher();

            cout<<"Variable manager Contenue\n"<<VariableManager::giveInstance(&LitteraleManager::giveInstance());

        }catch(exception& e){

            string A = e.what();
            cout << A << endl;
            Pile::afficher();

        }

		cout << "Veuillez saisir une valeur ou q pour arreter: ";
		cin.clear();
		getline(cin, s);
	}
}

