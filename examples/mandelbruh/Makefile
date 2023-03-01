NAME = mandelbruh.exe
XLIB_DIR = ../../
CC = g++
SRC = \
	mandelbruh.cpp
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC)
	make -C $(XLIB_DIR)
	$(CC) $(FLAGS) $(SRC) -I$(XLIB_DIR)/include -L$(XLIB_DIR) -lxlib -lSDL2main -lSDL2 -o $(NAME)

clean:
	make -C $(XLIB_DIR) fclean
	rm -rf $(NAME)