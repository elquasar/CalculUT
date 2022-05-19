#include "../include/OperateurManager.h"

using namespace std;

void OperateurManager::FaireOperation(const std::string OperateurS){

    if( OperateurS == "+"){

        auto opAdd = Add();
        opAdd.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "-" ){

        auto opSub = Sub();
        opSub.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "*" ){

        auto opMul = Mul();
        opMul.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "/" ){

        auto opDiv = Div();
        opDiv.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "DIV" ){

        auto opDivEntiere = DivEntiere();
        opDivEntiere.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "MOD" ){

        auto opMod = Mod();
        opMod.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "NEG" ){

        auto opNeg = Neg();
        opNeg.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "=" ){

        auto opEq = Eq();
        opEq.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "!=" ){

        auto opNotEq = NotEq();
        opNotEq.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "=<" ){

        auto opInfEq = InfEq();
        opInfEq.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == ">=" ){

        auto opSupEq = SupEq();
        opSupEq.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "<" ){

        auto opInf = Inf();
        opInf.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == ">" ){

        auto opSup = Sup();
        opSup.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "AND" ){

        auto opAnd = And();
        opAnd.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "OR" ){

        auto opOr = Or();
        opOr.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "NOT" ){

        auto opNot = Not();
        opNot.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "EVAL" ){

        /**<Ajouter EVAL!*/
        auto opEval = Eval();
        opEval.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "DUP" ){

        auto opDup = Dup();
        opDup.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "DROP" ){

        auto opDrop = Drop();
        opDrop.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "SWAP" ){

        auto opSwap = Swap();
        //cout<<OperateurS<<endl;
        opSwap.eval();

    }else if( OperateurS == "CLEAR" ){

        auto opClear = Clear();
        opClear.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "IFT" ){

        /**<Ajouter IFT!*/
        auto opIft = Ift();
        opIft.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "STO" ){

        /**<Ajouter STO!*/
        auto opSto = Sto();
        opSto.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "NUM" ){

        auto opNum = Num();
        opNum.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "DEN" ){

        auto opDen = Den();
        opDen.eval();
        //cout<<OperateurS<<endl;

    }else if( OperateurS == "FORGET" ){

        /**<Ajouter FORGET*/
        auto opForget = Forget();
        opForget.eval();
        //cout<<OperateurS<<endl;

    }

}

/**<"cestunOperateur" permet identifier si l'operateur forme parti de l'ensemble des operateurs garde*/
bool OperateurManager::cestunOperateur(string A) const{

    for(const string Operateur : Operateurs){

        if( A == Operateur ) return true;

    }

    return false;

}
