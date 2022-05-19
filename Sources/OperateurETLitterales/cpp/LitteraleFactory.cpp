#include "../include/LitteraleFactory.h"

Factory_Litterale::Factory_Litterale() {

    //std::cout << "Je suis une fabrique à litterale" << std::endl;

}

std::vector<long long> Factory_Litterale::toRatio(const std::string& chaine) {

    size_t found = chaine.find('/');
    std::string num = chaine.substr(0,found);
    std::string den = chaine.substr(found + 1, chaine.size() - found + 1);

    std::vector<long long> result;

    result.push_back(stoll(num));
    result.push_back(stoll(den));

    return result;
}


double Factory_Litterale::toReel(const std::string& chaine) {

    return (std::stod(chaine));

}

long long Factory_Litterale::toInt(const std::string& chaine) {

    return(std::stoll(chaine));

}


bool Factory_Litterale::IsRatio(const std::string& chaine){

    // On cherche l'occurence du char '/' dans la chaine de caractère

    size_t found = chaine.find('/');

    // On regarde si le denominateur et le numerateur ne sont pas reel :


    if (found == std::string::npos) {
        return false;
    }
    else {

        std::string num = chaine.substr(0,found);
        std::string den = chaine.substr(found + 1, chaine.size() - found + 1);

        if (IsInt(num) && IsInt(den)) {
            return true;
        }

    }
    return false;
}

bool Factory_Litterale::IsInt(const std::string& chaine) {

    if(chaine.empty() || chaine.find_first_not_of("-0123456789") != std::string::npos) {

        return false;
    }
    else {
        return true;
    }


}

bool Factory_Litterale::IsReel(const std::string& chaine) {

    size_t found = chaine.find('.');

    if (found != std::string::npos && !IsExpr(chaine)) {
        return true;
    }
    else {
        return false;
    }

}

std::string Factory_Litterale::removeSpaces(std::string input)
{
  input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
  return input;
}



bool Factory_Litterale::IsExpr(const std::string& chaine) {

    // une expression contient au moins 3 caractères

    if (chaine.size() < 3) {
        return false;
    }

    char first = chaine[0];
    char last  = chaine[chaine.size() - 1];

    // Si les premiers et derniers element sont ' et que la chaine de caractère
    // entre ces '' est atomique, alors c'est une expression
    if (first == '\'' && last == '\'' && IsAtome(chaine.substr(1,chaine.size()-2))) {
        return true;
    }
    return false;
}

bool Factory_Litterale::IsAtome(const std::string& chaine) {

    if(!isupper(chaine[0])) {
      return false;
    }
    for(size_t i = 1; i < chaine.size(); i++) {

        if(!isupper(chaine[i]) && !isdigit(chaine[i])){
            return false;
        }
    }
  return true;
}


bool Factory_Litterale::IsProg(const std::string& chaine) {

    char first = chaine[0];
    char last  = chaine[chaine.size() - 1];

    if (first == '[' && last == ']') {
        return true;
    }
    return false;

}



Litterale* Factory_Litterale::create(const std::string& chaine) {

    // On recoit une chaine de caractère qui est pralablement séparée en fonction
    // des espaces

    // Exemple : on recoit 'X1', on regarde le premier element de la chaine
    // si c un ' on sait que c'est une expression

    if (IsExpr(chaine)) {
        //std::cout << "Je fabrique une expression" << std::endl;
        return new LitteraleExpression(chaine);
    }

    // si c une majuscule en premier c un atome

    else if (IsAtome(chaine)) {

        //std::cout << "Je fabrique un atome" << std::endl;
        return new LitteraleAtome(chaine);
    }

    else if (IsProg(chaine)) {

        //std::cout << "Je fabrique un programme" << std::endl;
        return new LitteraleProgramme(chaine);
    }

    // sinon c un nombre, reste a determiner quel type de nombre ..



    else if (IsReel(chaine)) {

            //std::cout << "Je fabrique un reel" << std::endl;
            return new LitteraleReelle(toReel(chaine));
    }

    else if (IsRatio(chaine)) {



        //std::cout << "Je fabrique un rationnel" << std::endl;
        std::vector<long long> frac = toRatio(chaine);

        if (frac[1] == 0) {
            throw LitteraleException("LITTERALE : le denominateur ne doit pas etre nul");
            return nullptr;
    }
        return new LitteraleRatio(frac[0],frac[1]);
    }

    else if (IsInt(chaine)) {

        //std::cout << "Je fabrique un entier" << std::endl;
        return new LitteraleInt(toInt(chaine));
    }
    else {
        throw LitteraleException("LITTERALE : Votre entrée ne correspond à aucune litterale");
        return nullptr;
    }
}
