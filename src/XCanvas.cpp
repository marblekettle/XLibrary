#include "XCanvas.hpp"
#include <iostream>
#include <cstdlib>
using namespace XLibrary;

XCanvas::~XCanvas() {
	SDL_DestroyWindow(_win);
}

XCanvas::XCanvas(const char* title, int width, int height): \
	_title(title), _w(width), _h(height), _ready(false) {
	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_Init(SDL_INIT_VIDEO))
			throw (XGenericException("SDL not initialized."));
		atexit(SDL_Quit);
	}
	if (_w < 1 || _h < 1)
		throw (XGenericException("Invalid canvas size."));
	_win = SDL_CreateWindow(title, UNDEF, UNDEF, \
		width, height, SDL_WINDOW_SHOWN);
	if (!_win)
		throw (XGenericException("Cannot create window."));
	_srf = SDL_GetWindowSurface(_win);
	SDL_LockSurface(_srf);
	_ready = true;
	update();
}

SDL_Window&	XCanvas::getWindow() const {
	return (*_win);
}

std::string	XCanvas::getTitle() const {
	return (_title);
}

int			XCanvas::getWidth() const {
	return (_w);
}

int			XCanvas::getHeight() const {
	return (_h);
}

bool		XCanvas::isReady() const {
	return (_ready);
}

void		XCanvas::setTitle(const std::string& title) {
	_title = title;
}

void		XCanvas::setWidth(int width) {
	_w = width;
}

void		XCanvas::setHeight(int height) {
	_h = height;
}

void		XCanvas::update() {
	if (_ready)
		SDL_UpdateWindowSurface(_win);
}

void		XCanvas::refresh() {
	_ready = false;
	SDL_DestroyWindow(_win);
	try {
		_win = SDL_CreateWindow(_title.c_str(), UNDEF, UNDEF, \
			_w, _h, SDL_WINDOW_SHOWN);
		if (!_win)
			throw (XGenericException("Cannot create window."));
		_srf = SDL_GetWindowSurface(_win);
		_ready = true;
		update();
	} catch(const char* err) {
		std::cerr << "Error: " << err << std::endl;	
	}
}

void		XCanvas::blit(SDL_Surface* img, SDL_Rect* rect) {
	if (_ready) {
		SDL_UnlockSurface(_srf);
		SDL_BlitSurface(img, rect, _srf, NULL);
		SDL_LockSurface(_srf);
		this->update();
	}
}

void		XCanvas::setPixel(int x, int y, SDL_Color& color) {
	if (_srf && x >= 0 && x < _w && y >= 0 && y < _h) {
		char*	pixels = reinterpret_cast<char*>(_srf->pixels);
		uint32_t*	place = reinterpret_cast<uint32_t*>(pixels + \
			(_srf->format->BytesPerPixel * x) + (_srf->pitch * y));
		uint32_t	pixel = SDL_MapRGB(_srf->format, \
			color.r, color.g, color.b);
		*place = pixel;
	}
}

void		XCanvas::putPixel(int x, int y, SDL_Color& color) {
	if (_ready) {
		setPixel(x, y, color);
		this->update();
	}
}