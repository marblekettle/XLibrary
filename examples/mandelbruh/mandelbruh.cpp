#include "XLibrary.hpp"
using namespace XLibrary;

double	g_factor = 300.0;

int	is_in_set(double x, double y) {
	double a;
	double b;

	a = 0;
	b = 0;
	for (int iter = 0; iter < 100; iter++) {
		double t = a;
		a = (a * a) - (b * b) + x;
		b = (2 * t * b) + y;
		if ((a * a) + (b * b) > 2.0)
			return (255 - (4 * iter));
		if ((a * a) + (b * b) < 0.01 && iter < 20)
			break ;
	}
	return (0);
}

void	mandel(XCanvas& canvas) {
	for (int i = 0; i < 900; i++) {
		for (int j = 0; j < 600; j++) {
			double coords[2];
			coords[0] = (i - 600) / g_factor;
			coords[1] = (j - 300) / g_factor;
			SDL_Color	color;
			color.r = is_in_set(coords[0], coords[1]);
			color.g = 0;
			color.b = 0;
			canvas.setPixel(i, j, color);
		}
	}
}

bool	zoom_in(void* canvas) {
	g_factor *= 2.0;
	mandel(*(reinterpret_cast<XCanvas*>(canvas)));
	reinterpret_cast<XCanvas*>(canvas)->update();
	return (true);
}

bool	zoom_out(void* canvas) {
	g_factor *= 0.5;
	mandel(*(reinterpret_cast<XCanvas*>(canvas)));
	reinterpret_cast<XCanvas*>(canvas)->update();
	return (true);
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
	keymap.addPressKey(SDL_SCANCODE_UP, zoom_in, &canvas);
	keymap.addPressKey(SDL_SCANCODE_DOWN, zoom_out, &canvas);
	keymap.linkSetting(setting);
	clock.setSetting(setting);
	clock.start();
	return (0);
}
