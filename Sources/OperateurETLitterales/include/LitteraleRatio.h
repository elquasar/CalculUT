#ifndef LITERRALERATIO_H
#define LITERRALERATIO_H

#include "LitteraleReelle.h"

class LitteraleRatio : public LitteraleReelle {

    protected :
        // double value;
        long long den;
        long long num;

        void simplification();
        virtual std::ostream& print(std::ostream& out) const override;

    public :
        // constructeur

        LitteraleRatio(long long _num, long long _den);

        // getteurs

        inline long long getDen() const {return this->den;}
        inline long long getNum() const {return this->num;}


        // Opérateurs
        LitteraleRatio operator+(const LitteraleRatio& L);
        LitteraleRatio operator-(const LitteraleRatio& L);
        LitteraleRatio operator*(const LitteraleRatio& L);
        LitteraleRatio operator/(const LitteraleRatio& L);

};

inline bool operator==(const LitteraleRatio& R1, const LitteraleRatio& R2) { return (R1.getNum()*R2.getDen()) == (R2.getNum()*R1.getDen()); }
inline bool operator!=(const LitteraleRatio& R1, const LitteraleRatio& R2) { return (R1.getNum()*R2.getDen()) != (R2.getNum()*R1.getDen()); }
inline bool operator<(const LitteraleRatio& R1, const LitteraleRatio& R2) { return (R1.getNum()*R2.getDen()) < (R2.getNum()*R1.getDen()); }
inline bool operator<=(const LitteraleRatio& R1, const LitteraleRatio& R2) { return (R1.getNum()*R2.getDen()) <= (R2.getNum()*R1.getDen()); }
inline bool operator>(const LitteraleRatio& R1, const LitteraleRatio& R2) { return (R1.getNum()*R2.getDen()) > (R2.getNum()*R1.getDen()); }
inline bool operator>=(const LitteraleRatio& R1, const LitteraleRatio& R2) { return (R1.getNum()*R2.getDen()) >= (R2.getNum()*R1.getDen()); }

#endif
