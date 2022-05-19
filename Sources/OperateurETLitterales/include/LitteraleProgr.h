#ifndef LITTERALEPROG_H
#define LITTERALEPROG_H

#include "Litterale.h"
#include <string>
#include <iostream>
class LitteraleProgramme : public Litterale {

    public :

        std::string getValue();
        LitteraleProgramme(std::string _value);
        ~LitteraleProgramme();
        std::ostream& print(std::ostream& out) const override;

    private :

        std::string value;


};


#endif
