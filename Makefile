NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	./src/main.cpp			\
	  		./src/Core.cpp			\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ./include
CXXFLAGS +=  -Wall -Wextra -std=gnu++17
LXXFLAGS = -ldl


all: $(NAME)

$(NAME): $(OBJS)
	@make -C Nibbler/ re
	$(CC) $(OBJS) -o $(NAME) $(LXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

lib:
	make -C ./src/SDL/
	make -C ./src/SFML/

fclean: clean
	$(RM) $(NAME)

re: fclean all

lib-debug: CXXFLAGS += -g3
lib-debug:
	make -C ./src/SDL/ debug
	make -C ./src/SFML/ debug

debug: CXXFLAGS += -g3
debug: re

.PHONY: all clean fclean re lib
