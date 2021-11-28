#include "XS_Core.hpp"

XS_Core::~XS_Core()
{
	return ;
}

XS_Core::XS_Core(const char *title, int width, int height, int frame_time): \
	XS_Canvas(title, width, height), XS_Clock(frame_time), XS_Keymap()
{
	this->link(*this);
}

XS_Core::XS_Core(const XS_Core &copy): XS_Canvas(copy._title.c_str(), \
	copy._w, copy._h)
{
	*this = copy;
}

XS_Core		&XS_Core::operator=(const XS_Core &assign)
{
	XS_Clock::operator=(assign);
	XS_Keymap::operator=(assign);
	XS_Canvas::operator=(assign);
	this->link(*this);
	return (*this);
}
