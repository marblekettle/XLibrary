#include "XCanvas.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

XCanvas::~XCanvas() {
	SDL_DestroyWindow(_win);
}

XCanvas::XCanvas(const char* title, int width, int height): \
	_title(title), _w(width), _h(height), _ready(false) {
	try {
		if (!SDL_WasInit(SDL_INIT_VIDEO)) {
			if (SDL_Init(SDL_INIT_VIDEO))
				throw ("SDL not initialized.");
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
	catch (const char* err) {
		cerr << "Error: " << err << endl;
	}
}

SDL_Window&	XCanvas::getWindow() const {
	return (*_win);
}

string		XCanvas::getTitle() const {
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

void		XCanvas::setTitle(const string& title) {
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
			throw("Cannot create window.");
		_srf = SDL_GetWindowSurface(_win);
		_ready = true;
		update();
	} catch(const char* err) {
		std::cerr << "Error: " << err << std::endl;	
	}
}

void		XCanvas::blit(SDL_Surface* img, SDL_Rect* rect) {
	if (_ready) {
		SDL_BlitSurface(img, rect, _srf, NULL);
		this->update();
	}
}
