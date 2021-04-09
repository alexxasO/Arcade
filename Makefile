NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	./src/SFML/SFML_disp_module.cpp \
	  		./src/main.cpp			\
#			./src/SDL/SDL_disp_module.cpp \

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ./include
CXXFLAGS +=  -Wall -Wextra
LDFLAGS = -lSDL2 -lSDL2_ttf -lsfml-graphics -lsfml-system -lsfml-window

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

re: fclean

.PHONY: all clean fclean re
