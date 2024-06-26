#include "XClockSetting.hpp"
using namespace XLibrary;

XClockSetting::XClockSetting() {};

XClockSetting::~XClockSetting() {};

XClockSetting::XClockSetting(const XClockSetting& x) {
	*this = x;
}

XClockSetting&	XClockSetting::operator=(const XClockSetting& x) {
	this->_e_map = x._e_map;
	this->_p_map = x._p_map;
	return (*this);
}

void	XClockSetting::addEvent(Uint32 event, \
			bool (*func)(SDL_Event&, void*), void* ptr) {
	_e_map[event] = func;
	_p_map[event] = ptr;
}

void	XClockSetting::removeEvent(Uint32 event) {
	if (isEvent(event)) {
		_e_map.erase(event);
		_p_map.erase(event);
	}
}

bool	XClockSetting::isEvent(Uint32 event) const {
	return (_e_map.count(event) ? true : false);
}

bool	XClockSetting::runEvent(SDL_Event& event) {
	if (_e_map.count(event.type) == 0)
		throw (XUnknownEvent(event.type));
	return (_e_map[event.type](event, _p_map[event.type]));
}

XClockSetting::XUnknownEvent::XUnknownEvent(Uint32 event): \
	XGenericException("Unknown event: " + event) {};
