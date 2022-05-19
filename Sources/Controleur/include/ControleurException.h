#ifndef CONTROLEUREXCEPTION_H_INCLUDED
#define CONTROLEUREXCEPTION_H_INCLUDED

using namespace std;

class ControleurException : public exception {

private:

   std::string info;

public:

    ControleurException(const std::string& i) noexcept : info(i) {}
    ~ControleurException() noexcept {}
    const char* what() const noexcept {return info.c_str(); }

};

#endif // CONTROLEUREXCEPTION_H_INCLUDED
