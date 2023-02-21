SRCS_EXEC       =		src/main.c \
							src/signal/signal_handle.c \
								src/built_in/do_built_in.c \
								src/built_in/ft_cd.c \
								src/built_in/ft_echo.c \
								src/built_in/ft_env.c \
								src/built_in/ft_exit.c \
								src/built_in/ft_export.c \
								src/built_in/ft_pwd.c \
								src/built_in/ft_unset.c \
									src/utils/env.c \
									src/utils/error.c \
									src/utils/parsing_tools.c\

SRCS_PARS		=		src/parsing/cmdlist_tools.c \
						src/parsing/free.c \
						src/parsing/idlist_ctrl.c \
						src/parsing/idlist_tools.c \
						src/parsing/lexer.c \
						src/parsing/parsing.c 

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
				@$(CC) $(FLAGS) $(OBJS_EXEC) $(OBJS_PARS) $(HEADERS) $(LIB_PATH) -o $(NAME)
				@echo "Makefile : minishell crated"


all:            $(NAME)

clean:			
				@make clean -C libft
				@$(RM) $(OBJS_EXEC) $(OBJS_PARS)
				@echo "Makefile : minishell objects removed"

fclean:         clean
				@make fclean -C libft
				@$(RM) $(NAME)
				@echo "Makefile : minishell removed"

re:             fclean all
