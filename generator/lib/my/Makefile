##
## EPITECH PROJECT, 2019
## Lib
## File description:
## Makefile
##

NAME	=	libmy.a

SRC	=	$(wildcard ./list/*.c)		\
		$(wildcard ./csfml/*.c)		\
		$(wildcard ./pointer/*.c)	\
		$(wildcard ./str/*.c)		\

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I../../include

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	$(NAME) all clean fclean re