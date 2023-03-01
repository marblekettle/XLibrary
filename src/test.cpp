#include "XCanvas.hpp"
#include "XClock.hpp"
#include "XKeyMap.hpp"
#include <iostream>
using namespace XLibrary;

int	g_counter = 0;

bool	Loop(void* data) {
	XCanvas* canvas = reinterpret_cast<XCanvas*>(data);
	SDL_Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	canvas->putPixel(g_counter % 300, g_counter / 300, color);
	g_counter++;
	return (true);
}

bool	SpacePress(void* data) {
	std::cerr << reinterpret_cast<XClock*>(data)->getTime() << std::endl;
	return (true);
}

int	main(int ac, char** av)
{
	(void)ac;
	(void)av;
	XCanvas	c("Bluh", 200, 200);
	XClock	cl(1);
	XClockSetting	set;
	XKeyMap	km;
	km.addPressKey(SDL_SCANCODE_SPACE, SpacePress, &cl);
	km.linkSetting(set);
	cl.setSetting(set);
	cl.setLoopFunction(Loop, &c);
	cl.start();
	return (0);
}
