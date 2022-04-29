#include <iostream>
#include "Exception.h"

Exception::Exception(const std::string& _errorLog)
	: errorLog(_errorLog)
{ }

void Exception::showErrorLog() const
{
	std::cout << "[Error : " << this->errorLog << ']' << std::endl;
}