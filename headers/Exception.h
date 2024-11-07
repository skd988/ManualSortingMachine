#pragma once
#include <exception>
#include <string>

using std::string;

class Exception : std::exception {
public:
	Exception(string msg = "");
	virtual char const* what() const;

private:
	string m_msg;
};