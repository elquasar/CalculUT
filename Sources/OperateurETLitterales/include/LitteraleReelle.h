#ifndef LITERRALEREELLE_H
#define LITERRALEREELLE_H

#include "LitteraleNum.h"

class LitteraleReelle : public LitteraleNum {


    public :

        LitteraleReelle(double _value);
        virtual std::ostream& print(std::ostream& out) const;

        // Opérateurs
        LitteraleReelle operator+(const LitteraleReelle& R);
        LitteraleReelle operator-(const LitteraleReelle& R);
        LitteraleReelle operator*(const LitteraleReelle& R);
        LitteraleReelle operator/(const LitteraleReelle& R);

};

inline bool operator==(const LitteraleReelle& R1, const LitteraleReelle& R2) { return (R1.getValue() == R2.getValue());}
inline bool operator!=(const LitteraleReelle& R1, const LitteraleReelle& R2) { return (R1.getValue() != R2.getValue()); }
inline bool operator<(const LitteraleReelle& R1, const LitteraleReelle& R2) { return (R1.getValue() < R2.getValue()); }
inline bool operator<=(const LitteraleReelle& R1, const LitteraleReelle& R2) { return (R1.getValue() <= R2.getValue()); }
inline bool operator>(const LitteraleReelle& R1, const LitteraleReelle& R2) { return (R1.getValue() > R2.getValue()); }
inline bool operator>=(const LitteraleReelle& R1, const LitteraleReelle& R2) { return (R1.getValue() >= R2.getValue()); }


#endif
