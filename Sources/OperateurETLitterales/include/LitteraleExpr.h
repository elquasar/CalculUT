#ifndef LITTERALEEXPR_H
#define LITTERALEEXPR_H

#include "LitteraleAtome.h"

class LitteraleExpression : public LitteraleAtome {


    public :

        virtual std::string getValue() override;

        LitteraleExpression(std::string _value);
        ~LitteraleExpression();
        virtual std::ostream& print(std::ostream& out) const override;


};
#endif
