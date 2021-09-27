#ifndef XS_CANVAS_HPP
# define XS_CANVAS_HPP
# ifndef UNDEF
#  define UNDEF SDL_WINDOWPOS_UNDEFINED
# endif
# ifndef DEF_WIDTH
#  define DEF_WIDTH 640
# endif
# ifndef DEF_HEIGHT
#  define DEF_HEIGHT 480
# endif
# include <SDL.h>
# include <string>

class	XS_Canvas
{
public:
				~XS_Canvas();
				XS_Canvas(const char *title, int width = DEF_WIDTH, \
					int height = DEF_HEIGHT);
				XS_Canvas(const XS_Canvas &copy);
	XS_Canvas	&operator=(const XS_Canvas &assign);
	
	SDL_Window	&getWindow();
	std::string	&getTitle();
	int			getWidth();
	int			getHeight();
	bool		isReady();

	void		setTitle(std::string &title);
	void		setWidth(int width);
	void		setHeight(int height);

	void		update();
	void		refresh();
	void		blit(SDL_Surface *img, SDL_Rect *rect = NULL);
	
private:
				XS_Canvas();
	SDL_Window	*_win;
	SDL_Surface	*_srf;
	std::string	_title;
	int			_w;
	int			_h;
	bool		_ready;
};

#endif