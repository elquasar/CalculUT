#ifndef LITTERALEATOME_H
#define LITTERALEATOME_H

#include "Litterale.h"
#include <string>
class LitteraleAtome:  public Litterale {

    protected :

        std::string value;
    public :

        virtual std::string getValue();
        void setValue(std::string v);
        LitteraleAtome(std::string _value);
        ~LitteraleAtome();
        virtual std::ostream& print(std::ostream& out) const;




};


#endif




