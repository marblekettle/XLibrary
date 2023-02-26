#ifndef XKEYMAP_HPP
# define XKEYMAP_HPP
# include <SDL2/SDL.h>
# include "XClockSetting.hpp"

typedef std::map<SDL_Scancode, bool (*)(void*)>	t_pressmap;

typedef	std::map<SDL_Scancode, bool>	t_heldmap;

typedef std::map<SDL_Scancode, void*>	t_ptrkeymap;

class	XKeyMap {
public:
	XKeyMap();
	~XKeyMap();
	XKeyMap(const XKeyMap& x);
	XKeyMap&	operator=(const XKeyMap& x);
	void	addPressKey(SDL_Scancode key, bool (*func)(void*), \
		void* data = NULL);
	void	removePressKey(SDL_Scancode key);
	void	linkSetting(XClockSetting& set);
	void	unlinkSetting(XClockSetting& set) const;
	bool	isKey(SDL_Scancode key);
	bool	pressKey(SDL_Scancode key);
	bool	isPressed(SDL_Scancode key) const;
	static bool	handle(SDL_Event& event, void* data);
	class UnknownKey : public std::exception {
	public:
		UnknownKey(SDL_Scancode key);
		const char*	what() const throw();
	private:
		SDL_Scancode	_key;
	};
private:
	t_heldmap	_h_map;
	t_pressmap	_k_map;
	t_ptrkeymap	_p_map;
};

#endif
