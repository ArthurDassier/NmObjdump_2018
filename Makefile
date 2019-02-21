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

NM	=	my_nm

DUMP	=	my_objdump

SRCS_NM	=	srcs/nm/nm.c						\
			srcs/nm/global/print.c				\
			srcs/nm/global/actions.c			\
			srcs/nm/global/actions_two.c		\
			srcs/nm/global/chainlist.c			\
			srcs/nm/global/push_swap.c			\
			srcs/nm/global/utils.c				\
			srcs/nm/three/found_type_three.c	\
			srcs/nm/three/nm_three.c			\
			srcs/nm/six/found_type_six.c		\
			srcs/nm/six/nm_six.c				\

SRCS_DUMP	=	srcs/objdump/objdump.c			\
				srcs/objdump/print_six.c		\
				srcs/objdump/obj_three.c		\
				srcs/objdump/print_three.c		\

OBJS_NM	=	$(SRCS_NM:.c=.o)

OBJS_DUMP	=	$(SRCS_DUMP:.c=.o)

all: nm objdump

nm: $(NM)

objdump: $(DUMP)

$(NM): $(OBJS_NM)
	$(CC) $(OBJS_NM) -o $(NM)

$(DUMP): $(OBJS_DUMP)
	$(CC) $(OBJS_DUMP) -o $(DUMP)

clean:
	$(RM) $(OBJS_NM)
	$(RM) $(OBJS_DUMP)

fclean: clean
	$(RM) $(NM)
	$(RM) $(DUMP)


re: fclean all

.PHONY: all clean fclean re
