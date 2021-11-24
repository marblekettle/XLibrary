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
				XS_Clock(int frame_time = 40, \
					bool (*loop_func)(void *) = NULL, \
					void *loop_data = NULL);
				XS_Clock(const XS_Clock &copy);
	XS_Clock	&operator=(const XS_Clock &assign);

	void		start();
	void		stop();
	void		setLoopFunction(bool (*func)(void *) = NULL, \
					void *data = NULL);
	void		addEvent(Uint32 event, bool (*func)(SDL_Event &, void *), \
					void *data = NULL);
	void		removeEvent(Uint32 event);

protected:
	void		__loop();
	t_eventmap	_e_map;
	t_ptrmap	_p_map;
	bool 		(*_l_func)(void *);
	void		*_l_data;
	int			_t;
	uint64_t	_frame;
	bool		_run;
};

#endif