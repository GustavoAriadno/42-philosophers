NAME	=	philo

CC		=	gcc
C_FLAGS	=	-c		\
			-Wall	\
			-Wextra	\
			-I include/

SRC_DIR	=	src
SRC		=	main.c	\
			free.c	\
			setup.c	\
			utils.c	\
			banquet.c

vpath %.c ${SRC_DIR}

OBJ_DIR	=	obj
OBJ		=	$(patsubst %.c, ${OBJ_DIR}/%.o, ${SRC})


all		:	${NAME}

${NAME}	:	${OBJ}
			${CC} -o $@ $^ -g -fsanitize=address

${OBJ_DIR}/%.o	:	%.c
			mkdir -p ${OBJ_DIR}
			${CC} ${C_FLAGS} -g $< -o $@

clean	:
			rm -rf ${OBJ_DIR}

fclean	:	clean
			rm -rf ${NAME}

re		:	fclean all

.PHONY	:	all test clean fclean re
