NAME = out
SRC = test.cpp \
XCanvas.cpp \
XClock.cpp \
XClockSetting.cpp
SDL_DIR = ..\..\SDL2\x86_64-w64-mingw32
INCLUDE_DIR = include\SDL2\

$(NAME):
	g++ $(SRC) -I$(SDL_DIR)\$(INCLUDE_DIR) -L$(SDL_DIR)\lib -lmingw32 -lSDL2main -lSDL2 -o $(NAME)