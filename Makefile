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

SRCS_NM	=	srcs/nm/nm.c						\
			srcs/nm/global/print.c				\
			srcs/nm/global/actions.c			\
			srcs/nm/global/actions_two.c		\
			srcs/nm/global/chainlist.c			\
			srcs/nm/global/push_swap.c			\
			srcs/nm/three/found_type_three.c	\
			srcs/nm/three/nm_three.c			\
			srcs/nm/six/found_type_six.c		\
			srcs/nm/six/nm_six.c				\


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
