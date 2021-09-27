#include "XS_Clock.hpp"

XS_Clock::~XS_Clock()
{
	return ;
}

XS_Clock::XS_Clock(XS_Canvas &canvas, int frame_time): \
	_canv(&canvas), _t(frame_time), _frame(0), _run(false)
{
	return ;
}

XS_Clock::XS_Clock(const XS_Clock &copy)
{
	*this = *this;
}

XS_Clock	&XS_Clock::operator=(const XS_Clock &assign)
{
	this->_run = 0;
	this->_canv = assign._canv;
	this->_t = assign._t;
	this->_frame = 0;
	return (*this);
}

void		XS_Clock::start()
{
	if (!_run)
	{
		_frame = 0;
		_run = true;
		__loop();
	}
}

void		XS_Clock::stop()
{
	if (_run)
		_run = false;
}

void		XS_Clock::addEvent(Uint32 event, bool (*func)(void *))
{
	_e_map[event] = func;
}

void		XS_Clock::removeEvent(Uint32 event)
{
	_e_map.erase(event);
}

void		XS_Clock::__loop()
{
	SDL_Event	event;

	while (_run)
	{
		while (SDL_PollEvent(&event))
		{
			if (_e_map.count(event.type))
				(_e_map[event.type])(&event);
			else if (event.type == SDL_QUIT)
				_run = false;
		}
		if (_canv)
			_canv->update();
		if (!_run)
			break ;
		SDL_Delay(_t);
		_frame++;
	}
}