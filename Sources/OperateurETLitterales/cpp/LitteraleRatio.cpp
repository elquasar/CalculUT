#include "../include/LitteraleRatio.h"

/**< NE PAS OUBLIER VERIFICATION DIFFERENT DE 0 POUR DENOMINATEUR!! */

/**< Consucteur de rationnel */

LitteraleRatio::LitteraleRatio(long long _num, long long _den) :
LitteraleReelle::LitteraleReelle((double)_num / (double)_den), den(_den),num(_num) {

    /**< if (_den == 0) { */
    /**<     throw ComputerException("ERREUR : dénominateur nul"); */
    /**<     return; */
    /**< } */


    this->simplification();
}

/**< La value d'un LitteraleRatio est obtenu en divisant le numerateur par le denominateur */

/**< Affichage d'un rationnel : */

std::ostream& LitteraleRatio::print(std::ostream& out) const {

    if (this->den == 1) {
        return out << this->num;
    }
    else {

    return out << this->num << " / " << this->den;
    }
}

/**< ============== SURCHARGE DES OPERATEURS ============================== */

/**< Opérateur + */
LitteraleRatio LitteraleRatio::operator+(const LitteraleRatio& L){

    LitteraleRatio res(this->num * L.den + this->den * L.num,this->den * L.den);
    return res;
}

/**< Opérateur - */

LitteraleRatio LitteraleRatio::operator-(const LitteraleRatio& L){

    LitteraleRatio res(this->num * L.den - this->den * L.num,this->den * L.den);
    return res;

}

/**< Opérateur * */

LitteraleRatio LitteraleRatio::operator*(const LitteraleRatio& L) {

    LitteraleRatio res(this->num * L.num, this->den*L.den);
    return res;
}

/**< Opérateur / */

LitteraleRatio LitteraleRatio::operator/(const LitteraleRatio& L) {

    LitteraleRatio res(this->num * L.den, this->den*L.num);
    return res;

}





void LitteraleRatio::simplification() {

/**< si le numerateur est 0, le denominateur prend la valeur 1 */
	if (this->num == 0) { this->den = 1; return; }

	/**< un denominateur ne devrait pas être 0; si c’est le cas, on sort de la méthode */
	if (this->den  == 0) return;

	/**< utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun Denominateur (PGCD)
	entre le numerateur et le denominateur */
	int a=this->num, b=this->den ;

	/**< on ne travaille qu’avec des valeurs positives... */
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	while (a != b) {
		if (a > b) a = a - b;
		else b = b - a;
	}

	/**< on divise le numerateur et le denominateur par le PGCD=a */
	this->num/=a;
	this->den /=a;
	/**< si le denominateur est négatif, on fait passer le signe - au denominateur */
	if (this->den <0) { this->den =-this->den ; this->num=-this->num; }

}
