NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	./src/main.cpp			\
	  		./src/Core.cpp			\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ./include -std=c++17
CXXFLAGS +=  -Wall -Wextra
CXXFLAGS += -std=gnu++17
LDFLAGS = -lSDL2 -lncurses -ldl

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CXXFLAGS += -g
debug: re

.PHONY: all clean fclean re
