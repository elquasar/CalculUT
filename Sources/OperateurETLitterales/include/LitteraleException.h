#ifndef LITTERALE_EXCEPTION
#define LITTERALE_EXCEPTION

#include<stdexcept>
#include <string>

class LitteraleException : public std::exception {

    private :

        std::string info;
    public : 

        LitteraleException(const std::string& i) noexcept : info(i) {}
	    virtual ~LitteraleException() noexcept {}
	    const char* what() const noexcept {return info.c_str(); }

};

#endif
