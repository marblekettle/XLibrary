#include "XS_Core.hpp"
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

bool	loop(void *ptr)
{
	XS_Canvas	*c = ((XS_Canvas **)ptr)[0];
	XS_Keymap	*km = ((XS_Keymap **)ptr)[1];
	if (km->isKeyDown(SDL_SCANCODE_SPACE))
		std::cout << "space" << std::endl;
	c->update();
	return (true);
}
/*
int	main(int ac, char **av)
{
	XS_Canvas c("Hi", 320, 240);
	XS_Clock cl(100, loop, &c);
	XS_Keymap km(cl);
	void	*data[2] = {&c, &km};
	SDL_Surface *img = SDL_LoadBMP("../brian.bmp");
	cl.setLoopFunction(loop, &data);
	c.blit(img);
//	cl.addEvent(SDL_KEYDOWN, test, &c);
	km.addKey(SDL_SCANCODE_1, test1, &c);
	km.addKey(SDL_SCANCODE_2, test2, &c);
	km.addKey(SDL_SCANCODE_ESCAPE, exitbutton, &cl);
	km.enable();
	cl.start();
	return (0);
}
*/

bool	stop_core(void *ptr)
{
	(static_cast<XS_Clock *>(ptr))->stop();
	return (false);
}

int	main(int ac, char **av)
{
//	XS_Core	core("Hello");
//	XS_Core core2(core);
	XS_Canvas c("Hello");
//	XS_Canvas c2(c);
	XS_Clock cl;
	//cl.start();
	//c.refresh();
	//core.addEvent(SDL_KEYDOWN, stop_core, &core);
	XS_Keymap core(cl);
	XS_Keymap core2(core);
	core.addKey(SDL_SCANCODE_SPACE, stop_core, &cl);
	core.enable();
	cl.start();
	c.refresh();
	//core = core2;
	std::cout << "a" << std::endl;
	cl.start();
	return (0);
}
