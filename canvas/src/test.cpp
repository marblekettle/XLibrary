#include "XCanvas.hpp"
#include "XClock.hpp"
#include "XKeyMap.hpp"
#include <iostream>

bool	SpacePress(void* data) {
	std::cerr << reinterpret_cast<XClock*>(data)->getTime() << std::endl;
	return (true);
}

int	main(int ac, char** av)
{
	(void)ac;
	(void)av;
	XCanvas	c("Bluh");
	XClock	cl;
	XClockSetting	set;
	XKeyMap	km;
	km.addPressKey(SDL_SCANCODE_SPACE, SpacePress, &cl);
	km.linkSetting(set);
	cl.setSetting(set);
	cl.start();
	return (0);
}
