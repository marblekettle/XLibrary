#include "XS_Canvas.hpp"
#include <iostream>
#include <cstdlib>

XS_Canvas::~XS_Canvas()
{
	SDL_DestroyWindow(_win);
}

XS_Canvas::XS_Canvas(const char *title, int width, int height): \
	_title(title), _w(width), _h(height), _ready(false)
{
	try
	{
		if (!SDL_WasInit(0))
		{
			if (SDL_Init(SDL_INIT_VIDEO) < 0)
				throw ("Cannot initialize SDL.");
			atexit(SDL_Quit);
		}
		if (_w < 1 || _h < 1)
			throw ("Invalid canvas size.");
		_win = SDL_CreateWindow(title, UNDEF, UNDEF, \
			width, height, SDL_WINDOW_SHOWN);
		if (!_win)
			throw ("Cannot create window.");
		_srf = SDL_GetWindowSurface(_win);
		_ready = true;
		update();
	}
	catch (const char &err)
	{
		std::cerr << "Error: " << err << std::endl;
	}
}

XS_Canvas::XS_Canvas(const XS_Canvas &copy)
{
	*this = copy;
}

XS_Canvas	&XS_Canvas::operator=(const XS_Canvas &assign)
{
	this->_ready = false;
	SDL_DestroyWindow(this->_win);
	this->_w = assign._w;
	this->_h = assign._h;
	this->_title = assign._title;
	try
	{
		this->_win = SDL_CreateWindow(this->_title.c_str(), UNDEF, UNDEF, \
			this->_w, this->_h, SDL_WINDOW_SHOWN);
		if (!this->_win)
			throw ("Cannot create window.");
		this->_srf = SDL_GetWindowSurface(this->_win);
		this->_ready = true;
		this->update();
	}
	catch (const char &err)
	{
		std::cerr << "Error: " << err << std::endl;
	}
	return (*this);
}

SDL_Window	&XS_Canvas::getWindow()
{
	return (*(this->_win));
}

std::string	&XS_Canvas::getTitle()
{
	return (this->_title);
}

int			XS_Canvas::getWidth()
{
	return (this->_w);
}

int			XS_Canvas::getHeight()
{
	return (this->_h);
}

bool		XS_Canvas::isReady()
{
	return (this->_ready);
}

void		XS_Canvas::setTitle(std::string &title)
{
	this->_title = title;
}

void		XS_Canvas::setWidth(int width)
{
	this->_w = width;
}

void		XS_Canvas::setHeight(int height)
{
	this->_h = height;
}

void		XS_Canvas::update()
{
	SDL_UpdateWindowSurface(this->_win);
}

void		XS_Canvas::refresh()
{
	*this = *this;
}

void		XS_Canvas::blit(SDL_Surface *img, SDL_Rect *rect)
{
	SDL_BlitSurface(img, rect, this->_srf, NULL);
	this->update();
}