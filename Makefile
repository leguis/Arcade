##
## Makefile for arcade in /home/sebastien/Rendu/arcade
## 
## Made by Sebastien Le Guischer
## Login   <sebastien@epitech.net>
## 
## Started on  Thu Mar 16 15:28:41 2017 Sebastien Le Guischer
## Last update Sun Apr  9 23:22:28 2017 meghenr
##


##LIB_LAPIN

NAME_LAPIN	= ./lib/Lib_arcade_libLapin.so

SRCS_LAPIN	= ./src/lib/lib_lapin/lapin.cpp \

OBJS_LAPIN	= $(SRCS_LAPIN:.cpp=.o)


LIBLAPIN_FLAGS	= -llapin -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lstdc++ -ldl -lm -L/home/${USER}/.froot/lib -I/home/${USER}/.froot/include

##LIB_SFML

NAME_SFML	= ./lib/Lib_arcade_libsfml.so

SRCS_SFML	= ./src/lib/lib_sfml/sfml.cpp \

OBJS_SFML	= $(SRCS_SFML:.cpp=.o)

LIBSFML_FLAGS	= -lsfml-graphics -lsfml-window -lsfml-system


##LIB_NCURSES

NAME_NCURSES	= ./lib/Lib_arcade_libncurses.so

SRCS_NCURSES	= ./src/lib/ncurses/NCurses.cpp \

OBJS_NCURSES	= $(SRCS_NCURSES:.cpp=.o)

LIBNCURSES_FLAGS	= -lncurses

##LIB_PACMAN

NAME_PACMAN	= ./games/pacman.so

SRCS_PACMAN	= ./src/games/pacman/Pacman.cpp \
		  ./src/games/Character.cpp \

OBJS_PACMAN	= $(SRCS_PACMAN:.cpp=.o)


##LIB_SNAKE

NAME_SNAKE	= ./games/snake.so

SRCS_SNAKE	= ./src/games/snake/Snake.cpp \
		  ./src/games/Character.cpp \

OBJS_SNAKE	= $(SRCS_SNAKE:.cpp=.o)

##LIB_CORE

NAME_CORE	= arcade

SRCS_CORE	= ./src/main.cpp \
		  ./src/games/Menu.cpp \

OBJS_CORE	= $(SRCS_CORE:.cpp=.o)

COREFLAGS	= -ldl -g3

##END

CPPFLAGS	+=  -fpic -c -Wall -Wextra -std=c++11 -I./include

RM		= rm -rf

GPP		= g++

all:		$(NAME_PACMAN) $(NAME_SNAKE) $(NAME_CORE)

lib:		$(NAME_SFML) $(NAME_NCURSES) $(NAME_LAPIN)

$(NAME_SFML):	$(OBJS_SFML)
	mkdir -p lib
	$(GPP) -o $(NAME_SFML) -shared $(OBJS_SFML) $(LIBSFML_FLAGS)

$(NAME_NCURSES):	$(OBJS_NCURSES)
	$(GPP) -o $(NAME_NCURSES) -shared $(OBJS_NCURSES) $(LIBNCURSES_FLAGS)

$(NAME_LAPIN):	$(OBJS_LAPIN)
	$(GPP) -o $(NAME_LAPIN) -shared $(OBJS_LAPIN) $(LIBLAPIN_FLAGS)

$(NAME_PACMAN): $(OBJS_PACMAN)
	mkdir -p games
	$(GPP) -o $(NAME_PACMAN) -shared $(OBJS_PACMAN)

$(NAME_SNAKE): $(OBJS_SNAKE)
	$(GPP) -o $(NAME_SNAKE) -shared $(OBJS_SNAKE)

$(NAME_CORE):	$(OBJS_CORE)
	$(GPP) -o $(NAME_CORE) $(OBJS_CORE) $(COREFLAGS)

clean:
	$(RM) $(OBJS_LAPIN)
	$(RM) $(OBJS_PACMAN)
	$(RM) $(OBJS_CORE)
	$(RM) $(OBJS_SNAKE)
	$(RM) $(OBJS_SFML)
	$(RM) $(OBJS_NCURSES)

fclean:		clean
	$(RM) $(NAME_LAPIN)
	$(RM) $(NAME_PACMAN)
	$(RM) $(NAME_CORE)
	$(RM) $(NAME_SNAKE)
	$(RM) $(NAME_SFML)
	$(RM) $(NAME_NCURSES)
	$(RM) lib
	$(RM) games

re:		fclean all

.PHONY:		all clean fclean re
