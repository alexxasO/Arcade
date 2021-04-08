NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	./src/SDL/SDL_disp_module.cpp \
	  		./src/main.cpp			\
	  		./src/Core.cpp			\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ./include
CXXFLAGS +=  -Wall -Wextra
CXXFLAGS += -std=gnu++17
LDFLAGS = -lSDL2 -lncurses -ldl -lSDL2_ttf

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

lib: fclean
	make -C ./src/SDL/ re
	make -C ./src/SFML/ re

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CXXFLAGS += -g
debug: re

.PHONY: all clean fclean re
