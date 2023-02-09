# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 21:23:17 by efirmino          #+#    #+#              #
#    Updated: 2023/02/09 12:58:19 by efirmino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_EXEC       =		src/main.c \
						src/signal_handle.c \
						src/built_in/echo.c src/built_in/env.c src/built_in/exit.c \
						src/utils/env.c src/utils/error.c

SRCS_PARS		=		src/parsing.c src/parsing_tools.c src/free.c

OBJS_EXEC       =		$(SRCS_EXEC:.c=.o)

OBJS_PARS       =		$(SRCS_PARS:.c=.o)


RM              =		rm -f

CC              =		cc

FLAGS           =		-Wall -Wextra -Werror

USER			=		$(shell whoami)

HEADERS			=		-I/Users/$(USER)/.brew/opt/readline/include -I include

LIB_PATH		=		-L. libft/libft.a -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

NAME            =		minishell

.c.o:
				@$(CC) $(FLAGS) $(HEADERS) -c $< -o $(<:.c=.o)

$(NAME):        $(OBJS_EXEC) $(OBJS_PARS)
				@make -C libft
				$(CC) $(FLAGS) $(OBJS_EXEC) $(OBJS_PARS) $(HEADERS) $(LIB_PATH) -o $(NAME)


all:            $(NAME)

clean:
				@make clean -C libft
				$(RM) $(OBJS_EXEC) $(OBJS_PARS)

fclean:         clean
				@make fclean -C libft
				$(RM) $(NAME)

re:             fclean all
