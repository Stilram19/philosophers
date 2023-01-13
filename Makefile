SRCS=	philo/main.c \
		philo/utils.c \
		philo/room_of_fallacies.c \
		philo/room_of_fallacies_assist.c \
		philo/simulation.c
OBJS=	${SRCS:.c=.o}
CC=	cc
CFLAGS=	-Wall -Wextra -Werror
RM= rm -f
NAME= philoo

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all