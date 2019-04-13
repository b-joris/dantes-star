##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Solver Makefile
##

CC	=	gcc

SRC	=	./src/main.c	\
		./src/my_strlen.c	\
		./src/str_word_totab.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	solver

CFLAGS	=	-Wall -Wextra -g3

CPPFLAGS	=	-I./include -lmy -L./lib/my -g3

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C./lib/my
	$(CC) -o $(NAME) $(OBJ)

clean:
	make clean -C./lib/my
	rm -f $(OBJ)

fclean:	clean
	make fclean -C./lib/my
	rm -f $(NAME)

re:	fclean all

.PHONY: $(NAME) all clean re fclean
