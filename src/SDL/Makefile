##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## make
##

NAME	= arcade_sdl2.so

NAME2	= mytest

CC	= g++

RM	= rm -f

SRCDIR = ./

SRCS	=	$(SRCDIR)SDL_disp_module.cpp	\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ../../include
CXXFLAGS +=  -Wall -Wextra -fPIC
LXXFLAGS = -lSDL2 -lSDL2_ttf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(LXXFLAGS)
	mv $(NAME) ../../lib/

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../../lib/$(NAME)

re: fclean all

debug: CXXFLAGS += -g3
debug: re

.PHONY: all clean fclean re
