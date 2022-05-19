#include "../include/LitteraleAtome.h"

LitteraleAtome::LitteraleAtome(std::string _value) : value(_value) {}

std::string LitteraleAtome::getValue() {return this->value;}

std::ostream& LitteraleAtome::print(std::ostream& out) const {
    return (out << this->value);
}

void LitteraleAtome::setValue(std::string v) {this->value = v;}

LitteraleAtome::~LitteraleAtome()
{}
