#pragma once
#include "Litterale.h"
#include "LitteraleNum.h"
#include "LitteraleInt.h"
#include "LitteraleReelle.h"
#include "LitteraleRatio.h"
#include "LitteraleExpr.h"
#include "LitteraleProgr.h"
#include <vector>

class Operateur {
	const int arite;
protected:
	Operateur(int ar) : arite(ar) {};
	virtual void finDepilage(std::vector<Litterale*> operandes) const;
public:
	const int getArite() const { return arite; };
	void eval() const;
	virtual void exec(std::vector<Litterale*> operandes) const = 0;
};

class OpNullaire : public Operateur{
protected:
	OpNullaire() : Operateur(0) {};
public:
};

class OpUnaireNumerique : public Operateur {
protected:
	OpUnaireNumerique() : Operateur(1) {};
public:
};

class OpUnaireLogique : public Operateur {
protected:
	OpUnaireLogique() : Operateur(1) {};
public:
};

class OpUnaireProg : public Operateur {
protected:
	OpUnaireProg() : Operateur(1) {};
public:
};

class OpBinaireNumerique : public Operateur {
protected:
	OpBinaireNumerique() : Operateur(2) {};
public:
};

class OpBinaireLogique : public Operateur {
protected:
	OpBinaireLogique() : Operateur(2) {};
public:
};

class OpBinaireProg : public Operateur {
protected:
	OpBinaireProg() : Operateur(2) {};
public:
};

class Add : public OpBinaireNumerique {
public :
	void exec(std::vector<Litterale*> operandes) const override;
};

class Sub : public OpBinaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Mul : public OpBinaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Div : public OpBinaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class DivEntiere : public OpBinaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Mod : public OpBinaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Neg : public OpUnaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Eq : public OpBinaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class NotEq : public OpBinaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class InfEq : public OpBinaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class SupEq : public OpBinaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Inf : public OpBinaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Sup : public OpBinaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class And : public OpBinaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Or : public OpBinaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Not : public OpUnaireLogique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Dup : public OpUnaireNumerique {
protected:
	void finDepilage(std::vector<Litterale*> operandes) const override;
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Drop : public OpUnaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Swap : public OpBinaireProg {
protected:
	void finDepilage(std::vector<Litterale*> operandes) const override;
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Clear : public OpNullaire {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Eval : public OpUnaireProg {
public :
	void exec(std::vector<Litterale*> operandes) const override;
};

class Ift : public OpBinaireProg {
public :
	void exec(std::vector<Litterale*> operandes) const override;
};

class Sto : public OpBinaireProg {
protected:
	void finDepilage(std::vector<Litterale*> operandes) const override;
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Forget : public OpUnaireProg {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Num : public OpUnaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};

class Den : public OpUnaireNumerique {
public:
	void exec(std::vector<Litterale*> operandes) const override;
};
