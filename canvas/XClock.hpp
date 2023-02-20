#ifndef XCLOCK_HPP
# define XCLOCK_HPP
# include <iostream>
# include <Windows.h>
# include "XClockSetting.hpp"

class	XClock {
public:
	~XClock();
	XClock(uint32_t inter = 40, bool (*loop_func)(void*) = NULL, \
		void* loop_data = NULL);
	void		start();
	void		stop();
	void		setLoopFunction(bool (*func)(void*) = NULL, \
					void *data = NULL);
	void		setSetting(XClockSetting& set);
	void		removeSetting();
	XClockSetting*	getSetting();
	bool		lastReturn();
	uint32_t	getFrame();
	uint32_t	getTime();
	uint32_t	getInterval();
private:
	XClockSetting*	_set;
	bool 		(*_l_func)(void *);
	void*		_l_data;
	uint32_t	_in;
	uint64_t	_start;
	uint32_t	_t;
	uint32_t	_frame; 
	bool		_run;
	bool		_ret;
	bool		_ready;
				XClock(const XClock& copy);
	XClock&		operator=(const XClock& assign);
	void		__loop();
};

#endif