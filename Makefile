##
## EPITECH PROJECT, 2018
## lemipc
## File description:
## Makefile
##


NAME	=	lemipc

SRC	=	src/init.c	\
		src/main.c	\
		src/map.c	\
		src/sem.c	\
		src/sem_msgq.c	\
		src/soldier.c	\
		src/msg_func.c	\
		src/move_func.c
OBJ	= 	$(SRC:.c=.o)
CC	= 	gcc

CFLAGS	+= 	-W -Wall -Wextra -I./inc -lpthread -fno-stack-protector

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
