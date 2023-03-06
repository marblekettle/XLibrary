#include "XGenericException.hpp"
using namespace XLibrary;

XGenericException::XGenericException(std::string msg): _msg(msg) {};

const char*	XGenericException::what() const throw() {
	return (_msg.c_str());
}
