##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## make
##

NAME	= arcade_sfml.so

NAME2	= mytest

CC	= g++

RM	= rm -f

SRCDIR = ./

SRCS	=	$(SRCDIR)SFML_disp_module.cpp	\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ../../include
CXXFLAGS +=  -Wall -Wextra -fPIC
LXXFLAGS = -lsfml-graphics -lsfml-system -lsfml-window

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
