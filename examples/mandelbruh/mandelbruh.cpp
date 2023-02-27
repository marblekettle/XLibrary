#include "XLibrary.hpp"
using namespace XLibrary;

int	is_in_set(double x, double y) {
	double a;
	double b;

	a = 0;
	b = 0;
	for (int iter = 0; iter < 192; iter++) {
		double t = a;
		a = (a * a) - (b * b) + x;
		b = (2 * t * b) + y;
		if ((a * a) + (b * b) > 2.0)
			return (255 - (4 * iter));
	}
	return (0);
}

void	mandel(XCanvas& canvas) {
	for (int i = 0; i < 900; i++) {
		for (int j = 0; j < 600; j++) {
			double coords[2];
			coords[0] = (i - 600) / 300.0;
			coords[1] = (j - 300) / 300.0;
			SDL_Color	color;
			color.r = is_in_set(coords[0], coords[1]);
			color.g = 0;
			color.b = 0;
			canvas.setPixel(i, j, color);
		}
	}
}

bool	exit_canvas(void* clock) {
	reinterpret_cast<XClock*>(clock)->stop();
	return (false);
}

int	main(int ac, char** av)
{
	(void)ac;
	(void)av;
	XCanvas	canvas("Mandelbruh", 900, 600);
	mandel(canvas);
	canvas.update();
	XClock	clock;
	XClockSetting	setting;
	XKeyMap	keymap;
	keymap.addPressKey(SDL_SCANCODE_ESCAPE, exit_canvas, &clock);
	keymap.linkSetting(setting);
	clock.setSetting(setting);
	clock.start();
	return (0);
}
