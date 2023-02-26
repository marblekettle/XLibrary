#include "XClock.hpp"
using namespace std;

XClock::~XClock() {
	stop();
}

XClock::XClock(uint32_t inter, bool (*loop_func)(void*), void* loop_data): \
	_set(NULL), _l_func(loop_func), _l_data(loop_data), _in(inter), _t(0), \
	_frame(0), _run(false), _ret(false), _ready(false) {
	try {
		if (!SDL_WasInit(SDL_INIT_TIMER)) {
			if (SDL_Init(SDL_INIT_TIMER))
				throw ("SDL Timer not initialized.");
			atexit(SDL_Quit);
		}
		_ready = true;
	}
	catch (const char& err) {
		cerr << "Error: " << err << endl;
	}
}

void	XClock::start() {
	if (_ready && !_run) {
		_start = std::chrono::steady_clock::now();
		_frame = 0;
		_run = true;
		__loop();
	}
}

void	XClock::stop() {
	_run = false;
}

void	XClock::setLoopFunction(bool (*func)(void*), void* data) {
	_l_func = func;
	_l_data = data;
}

void	XClock::setSetting(XClockSetting& set) {
	_set = &set;
}

void	XClock::removeSetting() {
	_set = NULL;
}

XClockSetting*	XClock::getSetting() {
	return (_set);
}

bool	XClock::lastReturn() {
	return (_ret);
}

uint32_t	XClock::getFrame() {
	return (_frame);
}

uint32_t	XClock::getTime() {
	return (_t);
}

uint32_t	XClock::getInterval() {
	return (_in);
}

void		XClock::__loop() {
	SDL_Event	event;

	while (_run)
	{
		while (SDL_PollEvent(&event))
		{
			if (_set && _set->isEvent(event.type))
				_ret = _set->runEvent(event);
			else if (event.type == SDL_QUIT)
				_run = false;
		}
		if (!_run)
			break ;
		if (_l_func)
			_l_func(_l_data);
		SDL_Delay(_in);
		_t = std::chrono::duration_cast<std::chrono::milliseconds>( \
			std::chrono::steady_clock::now() - _start).count();
		_frame++;
	}
}

