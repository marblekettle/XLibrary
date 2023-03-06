#ifndef XCLOCKSETTING_HPP
# define XCLOCKSETTING_HPP
# include <SDL2/SDL.h>
# include <map>
# include <iostream>
# include "XGenericException.hpp"

namespace XLibrary {

typedef std::map<Uint32, bool (*)(SDL_Event&, void*)> t_eventmap;

typedef std::map<Uint32, void*> t_ptrmap;

class	XClockSetting {
public:
	XClockSetting();
	~XClockSetting();
	XClockSetting(const XClockSetting& x);
	XClockSetting&	operator=(const XClockSetting& x);
	void	addEvent(Uint32 event, bool (*func)(SDL_Event&, void*), void* ptr = NULL);
	void	removeEvent(Uint32 event);
	bool	isEvent(Uint32 event) const;
	bool	runEvent(SDL_Event& event);
	class	XUnknownEvent : public XGenericException {
	public:
		XUnknownEvent(Uint32 event);
	};
private:
	t_eventmap	_e_map;
	t_ptrmap	_p_map;
};

};

#endif
