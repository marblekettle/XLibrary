NAME = out
SRC = test.cpp XS_Canvas.cpp XS_Clock.cpp XS_Keymap.cpp XS_Core.cpp
SDL_DIR = ..\..\graphics\SDL2-2.0.16\x86_64-w64-mingw32
INCLUDE_DIR = include\SDL2\

$(NAME):
	g++ $(SRC) -I$(SDL_DIR)\$(INCLUDE_DIR) -L$(SDL_DIR)\lib -lmingw32 -lSDL2main -lSDL2 -o $(NAME)