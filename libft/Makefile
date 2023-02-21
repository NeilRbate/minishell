# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 17:43:00 by efirmino          #+#    #+#              #
#    Updated: 2023/02/06 21:43:02 by efirmino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_SRC		=	libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c \
					libft/ft_isalnum.c libft/ft_isalpha.c \
					libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c \
					libft/ft_itoa.c libft/ft_memchr.c \
					libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c \
					libft/ft_memset.c libft/ft_putchar_fd.c \
					libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
					libft/ft_putstr_fd.c libft/ft_strchr.c \
					libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c \
					libft/ft_strlcat.c libft/ft_strlcpy.c \
					libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c \
					libft/ft_strnstr.c libft/ft_strrchr.c \
					libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c \
					libft/ft_toupper.c libft/ft_split.c

GNL_SRC			=	get_next_line/get_next_line.c \
					get_next_line/get_next_line_utils.c 

FT_PRINTF_SRC	=	ft_printf/ft_printf.c ft_printf/ft_printf_utils.c \
					ft_printf/ft_printf_utils2.c


SRCS			=	$(LIBFT_SRC) $(GNL_SRC) $(FT_PRINTF_SRC)

OBJS			=	$(SRCS:.c=.o)

FLAGS			=	-Wall -Wextra -Werror

CC				=	cc

RM				=	rm -f

NAME			=	libft.a

.c.o:
		@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
		@ar rc $(NAME) $(OBJS)
		@echo "Makefile : libft created"

all:	$(NAME)

clean:
		@$(RM) $(OBJS)
		@echo "Makefile : libft objects have been erased"

fclean:	clean
		@$(RM) $(NAME)
		@echo "Makefile : libft have been erased"

re:	fclean all