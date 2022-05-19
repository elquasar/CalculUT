#include "../include/LitteraleProgr.h"

std::ostream& LitteraleProgramme::print(std::ostream& out) const {

    out << this->value;
    return out;

}

std::string LitteraleProgramme::getValue() {return this->value;}

LitteraleProgramme::LitteraleProgramme(std::string _value) : value(_value) {}
LitteraleProgramme::~LitteraleProgramme() {
    std::cout << "Destruction d'un programme" << std::endl;
}
