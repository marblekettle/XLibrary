#include "XS_Core.hpp"
#include <iostream>

bool	stop_core(void *ptr)
{
	(static_cast<XS_Core *>(ptr))->stop();
	return (false);
}

bool	loop(void *ptr)
{
	XS_Core *core = static_cast<XS_Core *>(ptr);
	if (true)
	{
	if (core->isKeyDown(SDL_SCANCODE_UP))
		std::cout << "up" << std::endl;
	if (core->isKeyDown(SDL_SCANCODE_DOWN))
		std::cout << core->getTime() << std::endl;
	}
	return (true);
}

int	main(int ac, char **av)
{
	XS_Core	core("Hello");
	core.addKey(SDL_SCANCODE_SPACE, stop_core, &core);
	core.setLoopFunction(loop, &core);
	core.enable();
	core.start();
	return (0);
}
