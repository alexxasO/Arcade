NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	./src/SDL_disp_module.cpp \
	  		./src/main.cpp			\
	  		./src/Menu.cpp			\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ./include -std=c++17
CXXFLAGS +=  -Wall -Wextra
LDFLAGS = -lSDL2 -ldl

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
