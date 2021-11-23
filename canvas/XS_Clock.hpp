#ifndef XS_CLOCK_HPP
# define XS_CLOCK_HPP
# include "XS_Canvas.hpp"
# include <map>

typedef std::map<Uint32, bool (*)(SDL_Event &, void *)> t_eventmap;

typedef std::map<Uint32, void *> t_ptrmap;

class	XS_Clock
{
public:
				~XS_Clock();
				XS_Clock(XS_Canvas &canvas, int frame_time = 40);
				XS_Clock(const XS_Clock &copy);
	XS_Clock	&operator=(const XS_Clock &assign);

	void		start();
	void		stop();
	void		addEvent(Uint32 event, bool (*func)(SDL_Event &, void *), \
				void *data);
	void		removeEvent(Uint32 event);

private:
				XS_Clock();
	void		__loop();
	t_eventmap	_e_map;
	t_ptrmap	_p_map;
	XS_Canvas	*_canv;
	int			_t;
	uint64_t	_frame;
	bool		_run;
};

#endif