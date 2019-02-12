##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## a_makefile_for_projetcs
##

CC	=	gcc -g3

RM	=	rm -rf

CFLAGS	+= -Wall -Wextra

CFLAGS	+=	-I./include

NAME	=	my_nm

SRCS	=	srcs/nm.c					\
			srcs/global/print.c			\
			srcs/global/actions.c		\
			srcs/global/actions_two.c	\
			srcs/global/chainlist.c		\
			srcs/global/push_swap.c		\
			srcs/32/found_type32.c		\
			srcs/32/nm_32.c				\
			srcs/64/found_type64.c		\
			srcs/64/nm_64.c				\


OBJS	=	$(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re
