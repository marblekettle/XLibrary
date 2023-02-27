NAME = libxlib.a
CC = g++
SRC = \
	src\XCanvas.cpp \
	src\XClock.cpp \
	src\XClockSetting.cpp \
	src\XKeyMap.cpp
SDL_DIR = ..\..\SDL2\x86_64-w64-mingw32
INCLUDE_DIR = include
ifeq ($(OS), Windows_NT)
	RM_COMM = del /s
	MING_LIB = -lmingw32
else
	RM_COMM = rm -rf
endif
LIBS = $(MING_LIB) -lSDL2main -lSDL2
SDL_LIBS = -I$(SDL_DIR)\$(INCLUDE_DIR) -L$(SDL_DIR)\lib $(LIBS)
FLAGS = -Wall -Werror -Wextra

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -I$(INCLUDE_DIR) $(SDL_LIBS) -o $@

all: $(NAME) test.exe

$(NAME): $(SRC:.cpp=.o)
	ar -rc $(NAME) $(SRC:.cpp=.o)

test.exe: $(NAME)
	$(CC) $(FLAGS) src\test.cpp $(NAME) -I$(INCLUDE_DIR) $(SDL_LIBS) -o test.exe

clean:
	$(RM_COMM) src\*.o

fclean: clean
	$(RM_COMM) $(NAME)
	$(RM_COMM) test.exe

re: clean all
