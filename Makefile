GCC = gcc
SRCS = src/main.c src/parsing.c src/parsing_tools.c src/free.c
OBJS = ${SRCS:.c=.o}
NAME = test
LIB = libft/libft.a
CFLAGS = -Wall -Wextra -Werror

.c.o:
	@${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}

	@echo "<| Compiling LIBFT  |>"
	@make -C libft all
	@echo "<| Compiling project |>"
	@${GCC} ${CFLAGS} -o ${NAME} ${LIB} ${OBJS}
	@echo "<| Compiling success |>"

all: ${OBJS} ${NAME}

clean:
	@rm -f ${OBJS}
	@echo Everything is clean

fclean: clean
	@rm -f ${NAME}

re: fclean all

