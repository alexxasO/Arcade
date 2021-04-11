##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## compile programs
##

LIBDIR=		../lib/
INCDIR=		include/
SRCDIR=		src/

OBJ=		$(SRC:.cpp=.o)
SRC=		$(SRCDIR)Nibbler_game_module.cpp

CXXFLAGS=	-I $(INCDIR) -fPIC

NAME=		arcade_nibbler.so

##
## Rules
##

all: title $(NAME)

$(NAME): cc_title obj_title $(OBJ)
	@$(LD) -shared -o $(NAME) $(OBJ) $(CXXFLAGS) && $(CHECK_MSG)
	@mv $(NAME) $(LIBDIR)

clean: clean_title
	@$(RM) $(OBJ)
	$(CLEAN_MSG)

fclean:	clean
	@$(RM) ../lib/$(NAME)
	$(FCLEAN_MSG)

re:	fclean all

debug: CXXFLAGS += -g3
debug: re

%.o: %.cpp
	@$(CC) -c $^ -o $@ $(CXXFLAGS) && $(CC_MSG)

.PHONY: all clean fclean re debug

##
## Messages
##

CHECK_MSG=	$(ECHO) $(BOLD)$(GREEN)"\n\n\t     ╽ ─╼━━━━━━━━━╾─ ╽\n\t ╼━━┿╉"$(DEF)		\
			$(BOLD)"BUILD SUCCESS "$(GREEN)"╊┿━━╾\n\t     ╿ ─╼━━━━━━━━━╾─ ╿\n"$(DEF) ||	\
			$(ECHO) $(BOLD)$(RED)"\n\n\t     ╽ ─╼━━━━━━━━╾─ ╽\n\t ╼━━┿╉"$(DEF)			\
			$(BOLD)"BUILD FAILED "$(RED)"╊┿━━╾\n\t     ╿ ─╼━━━━━━━━╾─ ╿\n"$(DEF)

CLEAN_MSG=	@$(ECHO) '\t   '$(BOLD)$(WHITE)"CLEAN "$(BOLD)$(GREEN)"SUCCESS "✓$(DEF)
FCLEAN_MSG=	@$(ECHO) '\t   '$(BOLD)$(WHITE)"FCLEAN "$(BOLD)$(GREEN)"SUCCESS "✓'\n'$(DEF)

CC_MSG=		$(ECHO) -n $(BOLD)$(GREEN)"  [OK] "$(TEAL) ||	\
			$(ECHO) -n $(RED)"  [NO] "$(TEAL)$(DEF) &&		\
			$(ECHO) $< | rev | cut -d'/' -f 1 | rev &&		\
			$(ECHO) -n $(DEF)

##
## Titles
##

title:
	@$(ECHO) $(BOLD)$(BLUE)"        ╼┪  ─╼━━━━━━━━━━┷━━━━━━━━━━━━╾─  ┢╾"		\
	"\n    ╼━━━┿╉    "$(DEF)$(BOLD)BUILDING $(TEAL)$(NAME)						\
	"   "$(BOLD)$(BLUE)"╊┿━━━╾\n        ╼┩  ─╼━━━━━━━━━━┯━━━━━━━━━━━━╾─  ┡╾"	\
	$(DEF)

obj_title:
	@$(ECHO) $(WHITE) && $(ECHO) -n $(SRCDIR) | tr a-z A-Z |\
	sed 's/\//\./' | cut -zd'/' -f1 &&						\
	$(ECHO) -n $(WHITE)' '$(BLANCO)'/                  \n'$(DEF)

clean_title:
	@$(ECHO) $(BOLD)$(YELLOW)"\n        ╼┪  ─╼━━━━━━━━━━┷━━━━━━━━━━━━╾─  ┢╾"		\
	"\n    ╼━━━┿╉    "$(DEF)$(BOLD)CLEANING $(TEAL)$(NAME)							\
	"   "$(BOLD)$(YELLOW)"╊┿━━━╾\n        ╼┩  ─╼━━━━━━━━━━┯━━━━━━━━━━━━╾─  ┡╾"	\
	"\n"$(DEF)

cc_title:
	@$(ECHO) -n $(WHITE)"\n┧" && $(ECHO) -n ' '$(CC) | tr a-z A-Z
	@$(ECHO) ' '$(BLANCO)/'                           '$(DEF)
	@$(ECHO) $(BOLD)$(WHITE)┃ $(MAGENTA)$(CXXFLAGS)
	@$(ECHO) -n $(WHITE)╵

.PHONY: title obj_title clean_title cc_title

##
## Display
##

CC=			g++
ECHO=		/bin/echo -e
DEF=		"\e[m"
BLACK=		"\e[1;30m"
RED=		"\e[31m"
GREEN=		"\e[32m"
YELLOW=		"\e[33m"
BLUE=		"\e[34m"
MAGENTA=	"\e[35m"
TEAL=		"\e[1;36m"
WHITE=		"\e[1;37m"
BLINK=		"\e[5m"
BOLD=		"\e[1m"
BORDER=		"\e[9m"
BLANCO=		"\e[9;37m"
BLACKY=		"\e[9;30m"
FONT=		"\e[7m"
