#include "../include/LitteraleExpr.h"

LitteraleExpression::LitteraleExpression(std::string _value) : LitteraleAtome::LitteraleAtome(_value) {}

std::ostream& LitteraleExpression::print(std::ostream& out) const {
    return (out << this->value);
}
LitteraleExpression::~LitteraleExpression()
{
    std::cout << "Destruction d une expression" << std::endl;
}


std::string LitteraleExpression::getValue() {

    return (this->value.substr(1,this->value.size()-2));
}
