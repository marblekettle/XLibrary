#ifndef XS_KEYMAP_HPP
# define XS_KEYMAP_HPP
# include "XS_Clock.hpp"
# include <map>

typedef	std::map<SDL_Scancode, bool (*)(void *)> t_keymap;

class	XS_Keymap
{
public:
				~XS_Keymap();
				XS_Keymap();
				XS_Keymap(XS_Clock &clock);
				XS_Keymap(const XS_Keymap &copy);
	XS_Keymap	&operator=(const XS_Keymap &assign);

	void		link(XS_Clock &clock);
	void		unlink();

	static bool	keymapEventHandle(SDL_Event &event, void *keymap);
	void		addKey(SDL_Scancode key, bool (*func)(void *), void *data);
	void		removeKey(SDL_Scancode key);
	void		enable(bool on = true);
	void		disable();
private:
	bool		__evt(SDL_Event &event);
	t_keymap	_k_map;
	t_ptrmap	_p_map;
	XS_Clock	*_clock;
	bool		_enabled;
};

#endif