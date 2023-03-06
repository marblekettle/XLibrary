#ifndef XGENERICEXCEPTION_HPP
# define XGENERICEXCEPTION_HPP
# include <string>

namespace XLibrary {

class	XGenericException : public std::exception {
public:
	XGenericException(std::string msg);
	const char*	what() const throw();
private:
	std::string	_msg;
};

};

#endif
