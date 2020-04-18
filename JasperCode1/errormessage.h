#ifndef ERRORMSG_H
#define ERRORMSG_H
#include <string>

class ErrorMessage{
    std::string s;
public:
    ErrorMessage(std::string s);
    std::string getErrorMessage();
};

#endif
