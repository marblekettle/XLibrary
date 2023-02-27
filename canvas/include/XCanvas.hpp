#ifndef CANVAS_HPP
# define CANVAS_HPP
# ifndef UNDEF
#  define UNDEF SDL_WINDOWPOS_UNDEFINED
# endif
# ifndef DEF_WIDTH
#  define DEF_WIDTH 640
# endif
# ifndef DEF_HEIGHT
#  define DEF_HEIGHT 480
# endif
# include <SDL2/SDL.h>
# include <string>
using namespace std;

class	XCanvas {
public:
	~XCanvas();
	XCanvas(const char* title, int width = DEF_WIDTH, int height = DEF_HEIGHT);
	SDL_Window&	getWindow() const;
	string		getTitle() const;
	int			getWidth() const;
	int			getHeight() const;
	bool		isReady() const;
	void		setTitle(const string& title);
	void		setWidth(int width);
	void		setHeight(int height);
	void		update();
	void		refresh();
	void		blit(SDL_Surface* img, SDL_Rect* rect = NULL);
protected:
	SDL_Window*		_win;
	SDL_Surface*	_srf;
	string			_title;
	int				_w;
	int				_h;
	bool			_ready;
private:
	XCanvas();
	XCanvas(const XCanvas& copy);
	XCanvas&	operator=(const XCanvas& assign);
};

#endif