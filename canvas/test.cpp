#include "XS_Keymap.hpp"
#include <iostream>

typedef struct	s_resolutions
{
	int	res[4][2] = {{360, 240},
				{640, 480},
				{800, 600},
				{1024, 768}};
}				t_resolutions;


bool	test(SDL_Event &evt, void *ptr)
{
	t_resolutions	r;	
	int	keynum = evt.key.keysym.scancode - SDL_SCANCODE_1;
	if (keynum >= 0 && keynum <= 3)
	{
		((XS_Canvas *)ptr)->setWidth(r.res[keynum][0]);
		((XS_Canvas *)ptr)->setHeight(r.res[keynum][1]);
		((XS_Canvas *)ptr)->refresh();
	}
	return (true);
}

bool	test1(void *ptr)
{
	((XS_Canvas *)ptr)->setTitle("1");
	((XS_Canvas *)ptr)->refresh();
	return (true);
}

bool	test2(void *ptr)
{
	((XS_Canvas *)ptr)->setTitle("2");
	((XS_Canvas *)ptr)->refresh();
	return (true);
}

bool	exitbutton(void *ptr)
{
	((XS_Clock *)ptr)->stop();
	return (true);
}

int	main(int ac, char **av)
{
	XS_Canvas c("Hi", 320, 240);
	XS_Clock cl(c);
	XS_Keymap km(cl);
	SDL_Surface *img = SDL_LoadBMP("../brian.bmp");
	c.blit(img);
//	cl.addEvent(SDL_KEYDOWN, test, &c);
	km.addKey(SDL_SCANCODE_1, test1, &c);
	km.addKey(SDL_SCANCODE_2, test2, &c);
	km.addKey(SDL_SCANCODE_ESCAPE, exitbutton, &cl);
	km.enable();
	cl.start();
	return (0);
}