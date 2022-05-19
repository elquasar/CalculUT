#ifndef PILEEXCEPTION_H_INCLUDED
#define PILEEXCEPTION_H_INCLUDED

using namespace std;

class PileException : public exception {

private:

   std::string info;

public:

    PileException(const std::string& i) noexcept : info(i) {}
    ~PileException() noexcept {}
    const char* what() const noexcept {return info.c_str(); }

};

#endif // PILEEXCEPTION_H_INCLUDED
