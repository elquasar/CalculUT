#ifndef LITTERALE_FACTORY_H
#define LITTERALE_FACTORY_H

// manipulation de string
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
// nos classes littérales
#include "Litterale.h"
#include "LitteraleRatio.h"
#include "LitteraleInt.h"
#include "LitteraleReelle.h"
#include "LitteraleExpr.h"
#include "LitteraleAtome.h"
#include "LitteraleProgr.h"
// Gestion des exceptions
#include "LitteraleException.h"



class Factory_Litterale {

    public : 
        


        Factory_Litterale(); 
        static Litterale*           create       (const std::string& chaine);
        static std::string          removeSpaces (std::string input);
        
        static bool                   IsRatio (const std::string& chaine);
        static bool                   IsInt   (const std::string& chaine);
        static bool                   IsReel  (const std::string& chaine);
        static bool                   IsAtome (const std::string& chaine);
        static bool                   IsExpr  (const std::string& chaine); 
        static bool                   IsProg  (const std::string& chaine);
        
        static double                 toReel  (const std::string& chaine);
        static long long              toInt   (const std::string& chaine);
        static std::vector<long long> toRatio (const std::string& chaine);

};




#endif
