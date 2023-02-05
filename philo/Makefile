SRCS=	main.c \
		utils.c \
		room_of_fallacies.c \
		room_of_fallacies_assist.c \
		simulation.c
OBJS=	${SRCS:.c=.o}
CC=	cc
CFLAGS=	-Wall -Wextra -Werror
#CFLAGS+= -fsanitize=thread
RM= rm -f
NAME= philo

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all