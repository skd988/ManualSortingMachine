#include "Exception.h"

Exception::Exception(string msg) :
	m_msg(msg)
{

}

char const* Exception::what() const {
	return m_msg.c_str();
}