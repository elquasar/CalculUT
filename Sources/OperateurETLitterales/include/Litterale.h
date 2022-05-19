#ifndef LITTERALE_H
#define LITTERALE_H

#include <iostream>



class Litterale {

    public :

        virtual std::ostream& print(std::ostream& out) const = 0;
        // virtual int getDen() = 0;
        ~Litterale() { /*std::cout << "Destruction de litterale" << std::endl;*/ }


};

std::ostream& operator<<(std::ostream& out, const Litterale& litt);


#endif
