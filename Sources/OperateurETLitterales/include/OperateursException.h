#ifndef OPERATEURS_EXCEPTION
#define OPERATEURS_EXCEPTION

#include<stdexcept>
#include <string>

class OperateursException : public std::exception {

    private :

        std::string info;
    public :

        OperateursException(const std::string& i) noexcept : info(i) {}
	      virtual ~OperateursException() noexcept {}
	      const char* what() const noexcept {return info.c_str(); }

};

#endif
