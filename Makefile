##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## a_makefile_for_projetcs
##

CC	=	gcc

RM	=	rm -rf

CFLAGS	+= -Wall -Wextra

CFLAGS	+=	-I./include

NM	=	my_nm

SRCS_NM	=	srcs/nm/nm.c					\
			srcs/nm/global/print.c			\
			srcs/nm/global/actions.c		\
			srcs/nm/global/actions_two.c	\
			srcs/nm/global/chainlist.c		\
			srcs/nm/global/push_swap.c		\
			srcs/nm/32/found_type32.c		\
			srcs/nm/32/nm_32.c				\
			srcs/nm/64/found_type64.c		\
			srcs/nm/64/nm_64.c				\


OBJS_NM	=	$(SRCS_NM:.c=.o)

all: nm

nm: $(NM)

$(NM): $(OBJS_NM)
	$(CC) $(OBJS_NM) -o $(NM)

clean:
	$(RM) $(OBJS_NM)

fclean: clean
	$(RM) $(NM)


re: fclean all

.PHONY: all clean fclean re
