#pragma once

#include "string"

class Exception
{
private:
	const std::string errorLog;
public:
	explicit Exception(const std::string& _errorLog);
	void showErrorLog() const;
};