#include "XS_Clock.hpp"
#include <iostream>

bool	test(void *evt)
{
	SDL_Event *ev = (SDL_Event *)evt;
	std::cout << (int)(ev->key.keysym.scancode) << std::endl;
	return (1);
}

int	main(int ac, char **av)
{
	XS_Canvas c("Hi", 320, 240);
	XS_Clock cl(c);
	SDL_Surface *img = SDL_LoadBMP("../brian.bmp");
	c.blit(img);
	cl.addEvent(SDL_KEYDOWN, test);
	cl.start();
	return (0);
}