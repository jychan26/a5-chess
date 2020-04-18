#include "errormessage.h"
using std::string;

string ErrorMessage::getErrorMessage(){
  return s;
}

ErrorMessage::ErrorMessage(std::string s) : s{s} {}
