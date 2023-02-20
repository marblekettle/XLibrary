#include "XCanvas.hpp"
#include "XClock.hpp"
#include <iostream>

bool	KeyDown(SDL_Event& evt, void* data) {
	std::cout << evt.key.keysym.scancode << std::endl;
	return (true);
}

int	main(int ac, char** av)
{
	XCanvas	c("Bluh");
	XClock	cl;
	XClockSetting	set;
	set.addEvent(SDL_KEYDOWN, &KeyDown, &cl);
	cl.setSetting(set);
	cl.start();
	return (0);
}
