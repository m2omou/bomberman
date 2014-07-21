##
## Makefile for 42sh in /home/brissa_a//c/B2/42sh
## 
## Made by alexis brissard
## Login   <brissa_a@epitech.net>
## 
## Started on  Mon Apr  4 13:18:55 2011 alexis brissard
## Last update Sun Jun  3 18:35:10 2012 alexis brissard
##

CC=		g++

NAME=		bomberman

SRC=		$(wildcard src/*.cpp)

OBJ=		$(SRC:.cpp=.o)

CFLAGS=		-W -Wall -Wextra -O2

HEADERS=	-Ilibgdl_gl-2012.1/include					 \
		-Ilua-5.2_Linux26g4_64_lib/include				 \
		-ISLB/include/							 \
		-Ifmod/include/							 \
		-Isfml/include/

LIB=		-lpthread							 \
		-Llibgdl_gl-2012.1/lib -Wl,--rpath=libgdl_gl-2012.1/lib -lgdl_gl \
		-lGL								 \
		-lGLU								 \
		-Llua-5.2_Linux26g4_64_lib/lib/					 \
		-Wl,--rpath=lua-5.2_Linux26g4_64_lib/lib			 \
		-llua52								 \
		-LSLB/ -Wl,--rpath=SLB -lSLB					 \
		-Lfmod/ -lfmodex64-4.40.03 -Wl,-rpath,./fmod			 \
		-Lsfml/lib -Wl,--rpath=sfml/lib

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB)

.cpp.o:		$(SRC)
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all:		$(NAME)

clean:
		rm -f $(OBJ) ; rm -f *~

fclean:		clean
		rm -f $(NAME)

re: 		fclean all
