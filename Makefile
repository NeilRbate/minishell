# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 21:23:17 by efirmino          #+#    #+#              #
#    Updated: 2023/02/06 21:36:46 by efirmino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS            =       src/main.c 

OBJS            =   	$(SRCS:.c=.o)

RM              =       rm -f

CC              =       cc

FLAGS           =       -Wall -Wextra -Werror

LIB_PATH		=		-L. libft/libft.a -lreadline

NAME            =       minishell

.c.o:
				@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):        $(OBJS)
				@make -C libft
				$(CC) $(FLAGS) $(LIB_PATH) $(OBJS) -o $(NAME)


all:            $(NAME)

clean:
				@make clean -C libft
				$(RM) $(OBJS)

fclean:         clean
				@make fclean -C libft
				$(RM) $(NAME)

re:             fclean all