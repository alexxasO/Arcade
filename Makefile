NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	./src/SDL_disp_module.cpp \
	  		./src/main.cpp			\
	  		./src/Ncurses_disp_module.cpp			\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ./include
CXXFLAGS +=  -Wall -Wextra
LDFLAGS = -lSDL2 -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
