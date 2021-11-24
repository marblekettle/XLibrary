#include "XS_Keymap.hpp"

XS_Keymap::~XS_Keymap()
{
	if (_clock)
	{
		_clock->removeEvent(SDL_KEYDOWN);
		_clock->removeEvent(SDL_KEYUP);
	}
}

XS_Keymap::XS_Keymap(): _enabled(false), _clock(nullptr) {};

XS_Keymap::XS_Keymap(XS_Clock &clock): _enabled(false)
{
	link(clock);
};

XS_Keymap::XS_Keymap(const XS_Keymap &copy)
{
	*this = copy;
}

XS_Keymap	&XS_Keymap::operator=(const XS_Keymap &assign)
{
	this->_k_map = assign._k_map;
	this->_p_map = assign._p_map;
	this->link(*(assign._clock));
	this->_enabled = false;
	return (*this);
}

void	XS_Keymap::link(XS_Clock &clock)
{
	_clock = &clock;
	_clock->addEvent(SDL_KEYDOWN, XS_Keymap::keymapEventHandle, this);
	_clock->addEvent(SDL_KEYUP, XS_Keymap::keymapEventHandle, this);
}

void	XS_Keymap::unlink()
{
	_clock = nullptr;
}

bool	XS_Keymap::keymapEventHandle(SDL_Event &event, void *keymap)
{
	return (((XS_Keymap *)keymap)->__evt(event));
}

void	XS_Keymap::addKey(SDL_Scancode key, bool (*func)(void *), void *data)
{
	_k_map[key] = func;
	_p_map[key] = data;
}

void	XS_Keymap::removeKey(SDL_Scancode key)
{
	_k_map.erase(key);
	_p_map.erase(key);
}

void	XS_Keymap::enable(bool on)
{
	_enabled = on;
}

void	XS_Keymap::disable()
{
	_enabled = false;
}

bool	XS_Keymap::isKeyDown(SDL_Scancode key)
{
	return (static_cast<bool>(_keys.count(key)));
}

bool	XS_Keymap::__evt(SDL_Event &event)
{
	if (_enabled)
	{
		if (event.type == SDL_KEYDOWN)
		{
			SDL_Scancode key = event.key.keysym.scancode;
			_keys.insert(key);
			if (_k_map.count(key))
				return (_k_map[key](_p_map[key]));
		}
		else if (event.type == SDL_KEYUP)
		{
			SDL_Scancode key = event.key.keysym.scancode;
			_keys.erase(key);
		}
	}
	return (false);
}