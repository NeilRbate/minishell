GCC = gcc
SRCS = src/main.c src/parsing.c
OBJS = ${SRCS:.c=.o}
NAME = test
CFLAGS = -Wall -Wextra -Werror

.c.o:
	@${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@${GCC} ${CFLAGS} -o ${NAME} ${OBJS}
	@echo "<| Compiling success |>"

all: ${OBJS} ${NAME}

clean:
	@rm -f ${OBJS}
	@echo Everything is clean

fclean: clean
	@rm -f ${NAME}

re: fclean all

