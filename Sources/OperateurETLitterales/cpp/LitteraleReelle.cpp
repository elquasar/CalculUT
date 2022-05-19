#include "../include/LitteraleReelle.h"
LitteraleReelle::LitteraleReelle(double _value) : LitteraleNum(_value) {}


std::ostream& LitteraleReelle::print(std::ostream& out) const {
    return out << this->value;
}

/**< Opérations entre réels */

LitteraleReelle LitteraleReelle::operator+(const LitteraleReelle& R) {
    LitteraleReelle res(this->value + R.value);
    return res;
}


LitteraleReelle LitteraleReelle::operator-(const LitteraleReelle& R) {
    LitteraleReelle res(this->value - R.value);
    return res;
}

LitteraleReelle LitteraleReelle::operator*(const LitteraleReelle& R) {
    LitteraleReelle res(this->value * R.value);
    return res;
}

LitteraleReelle LitteraleReelle::operator/(const LitteraleReelle& R) {
    LitteraleReelle res(this->value / R.value);
    return res;
}
