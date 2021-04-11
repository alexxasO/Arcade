NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	./src/main.cpp			\
	  		./src/Menu.cpp			\
	  		./src/Core.cpp			\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ./include
CXXFLAGS +=  -Wall -Wextra -std=gnu++17 -Wl,-rpath=.
LXXFLAGS = -ldl


all: $(NAME)

$(NAME): $(OBJS) lib
	$(CC) $(OBJS) -o $(NAME) $(LXXFLAGS) $(LDFLAGS)

nibbler:
	@make -C Nibbler/ re

clean:
	$(RM) $(OBJS)

lib:
	make -C ./src/SDL/
	make -C ./src/SFML/
	make -C ./src/NCURSES/

fclean: clean
	$(RM) $(NAME)

re: fclean all

lib-debug: CXXFLAGS += -g3
lib-debug:
	make -C ./src/SDL/ debug
	make -C ./src/SFML/ debug
	make -C ./src/NCURSES/ debug

debug: CXXFLAGS += -g3
debug: re

.PHONY: all clean fclean re lib
