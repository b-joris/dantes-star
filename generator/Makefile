##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Generator Makefile
##

CC	=	gcc

SRC	=	./src/main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	generator

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I./include -lmy -L./lib/my

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C./lib/my
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	make clean -C./lib/my
	rm -f $(OBJ)

fclean:	clean
	make fclean -C./lib/my
	rm -f $(NAME)

re:	fclean all

.PHONY: $(NAME) all clean re fclean