# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 21:23:17 by efirmino          #+#    #+#              #
#    Updated: 2023/02/07 12:46:59 by efirmino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS       		=		src/main.c \
						src/signal_handle.c \
						src/echo.c

OBJS            =		$(SRCS:.c=.o)

RM              =		rm -f

CC              =		cc

FLAGS           =		-Wall -Wextra -Werror

USER			=		$(shell whoami)

HEADERS			=		-I/Users/efirmino/.brew/opt/readline/include -I include

LIB_PATH		=		-L. libft/libft.a -lreadline -L/Users/efirmino/.brew/opt/readline/lib

NAME            =		minishell

.c.o:
				@$(CC) $(FLAGS) $(HEADERS) -c $< -o $(<:.c=.o)

$(NAME):        $(OBJS)
				@make -C libft
				$(CC) $(FLAGS) $(OBJS) $(HEADERS) $(LIB_PATH) -o $(NAME)


all:            $(NAME)

clean:
				@make clean -C libft
				$(RM) $(OBJS)

fclean:         clean
				@make fclean -C libft
				$(RM) $(NAME)

re:             fclean all