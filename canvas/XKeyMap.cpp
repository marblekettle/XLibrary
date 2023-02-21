#include "XKeyMap.hpp"

XKeyMap::XKeyMap() {};

XKeyMap::~XKeyMap() {};

XKeyMap::XKeyMap(const XKeyMap& x) {
	*this = x;
}

XKeyMap&	XKeyMap::operator=(const XKeyMap& x) {
	this->_k_map = x._k_map;
	this->_p_map = x._p_map;
	this->_h_map.clear();
	return (*this);
}

void	XKeyMap::addPressKey(SDL_Scancode key, bool (*func)(void*), \
			void* data) {
	
	_k_map[key] = func;
	_p_map[key] = data;
}

void	XKeyMap::removePressKey(SDL_Scancode key) {
	if (isKey(key)) {
		_k_map.erase(key);
		_p_map.erase(key);
	}
}

void	XKeyMap::linkSetting(XClockSetting& set) {
	set.addEvent(SDL_KEYDOWN, handle, this);
	set.addEvent(SDL_KEYUP, handle, this);
}

void	XKeyMap::unlinkSetting(XClockSetting& set) const {
	set.removeEvent(SDL_KEYDOWN);
	set.removeEvent(SDL_KEYUP);
}

bool	XKeyMap::isKey(SDL_Scancode key) {
	return (_k_map.count(key) ? true : false);
}

bool	XKeyMap::pressKey(SDL_Scancode key) {
	if (!isKey(key))
		throw UnknownKey(key);
	return (_k_map[key](_p_map[key]));
}

bool	XKeyMap::isPressed(SDL_Scancode key) const{
	return (_h_map.count(key) && _h_map.at(key));
}

bool	XKeyMap::handle(SDL_Event& event, void* data) {
	XKeyMap*	kmap = reinterpret_cast<XKeyMap*>(data);
	if (event.type == SDL_KEYDOWN) {
		if (kmap->_k_map.count(event.key.keysym.scancode))
			kmap->pressKey(event.key.keysym.scancode);
		kmap->_h_map[event.key.keysym.scancode] = true;
	} else if (event.type == SDL_KEYUP)
		kmap->_h_map[event.key.keysym.scancode] = false;
	return (true);
}

XKeyMap::UnknownKey::UnknownKey(SDL_Scancode key): _key(key) {};

const char*	XKeyMap::UnknownKey::what() const throw() {
	std::string	s = "Unknown key: " + _key;
	return (s.c_str());
}
