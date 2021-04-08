NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	./src/SDL/SDL_disp_module.cpp \
	  		./src/main.cpp			\

OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS = -I ./include
CXXFLAGS +=  -Wall -Wextra
LDFLAGS = -lSDL2 -lSDL2_ttf

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

lib:
	make re -C ./src/SDL/
	make re -C ./src/SFML/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
