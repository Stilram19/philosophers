SRCS=	main.c \
		room_of_fallacies_bonus.c \
		room_of_fallacies_assist_bonus.c \
		utils.c \
		utils2.c \
		simulation_bonus.c
OBJS=	${SRCS:.c=.o}
NAME=	philo_bonus
CC=		cc
CFLAGS=	-Wall -Wextra -Werror
RM=		rm -f

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

bonus: ${NAME}

re: fclean all