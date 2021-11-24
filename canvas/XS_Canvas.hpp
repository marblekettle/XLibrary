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

typedef const std::string	t_cstring;

class	XS_Canvas
{
public:
				~XS_Canvas();
				XS_Canvas(const char *title, int width = DEF_WIDTH, \
					int height = DEF_HEIGHT);
				XS_Canvas(const XS_Canvas &copy);
	XS_Canvas	&operator=(const XS_Canvas &assign);
	
	SDL_Window	&getWindow() const;
	t_cstring	&getTitle() const;
	int			getWidth() const;
	int			getHeight() const;
	bool		isReady() const;

	void		setTitle(t_cstring &title);
	void		setWidth(int width);
	void		setHeight(int height);

	void		update();
	void		refresh();
	void		blit(SDL_Surface *img, SDL_Rect *rect = NULL);
	
protected:
	SDL_Window	*_win;
	SDL_Surface	*_srf;
	std::string	_title;
	int			_w;
	int			_h;
	bool		_ready;
private:
				XS_Canvas();
};

#endif