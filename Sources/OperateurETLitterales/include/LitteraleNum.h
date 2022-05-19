#ifndef LITTERALENUM_H
#define LITTERALENUM_H


#include <iostream>
#include "Litterale.h"

class LitteraleNum : public Litterale {

    protected : 

        double value;

    public : 
        
        LitteraleNum(double _value) : value(_value) {}
        
        
        inline virtual double getValue() const   {return this->value;};
        inline virtual void   setValue(double v) {this->value = v;}
};

// opérateur affichage




#endif
