SRCS_EXEC       =		src/main.c \
						src/basic_cmd.c \
						src/built_in_cmd.c \
						src/pipe_cmd.c \
							src/built_in/ft_cd.c \
							src/built_in/ft_echo.c \
							src/built_in/ft_env.c \
							src/built_in/ft_exit.c \
							src/built_in/ft_export.c \
							src/built_in/ft_pwd.c \
							src/built_in/ft_unset.c \
									src/utils/env.c \
									src/utils/env2.c \
									src/utils/free.c \
									src/signal_handle.c \
									src/utils/error_msg.c \

SRCS_PARS		=			src/parsing/cmdlist_tools.c \
							src/parsing/free.c \
							src/parsing/idlist_ctrl.c \
							src/parsing/idlist_tools.c \
							src/parsing/lexer.c \
							src/parsing/parsing.c \
							src/parsing/is_bultin.c \
							src/parsing/files_tools.c \
							src/parsing/dollar.c \
							src/parsing/redir.c \
							src/parsing/file_gestion.c \
							src/parsing/customft.c \
							src/parsing/redir2.c \
							src/parsing/syntaxerror.c

OBJS_EXEC       =		$(SRCS_EXEC:.c=.o) $(SRCS_PARS:.c=.o)

RM              =		rm -f

CC              =		cc

FLAGS           =		-Wall -Wextra -Werror

USER			=		$(shell whoami)

HEADERS			=		-I/opt/homebrew/opt/readline/include -I include

LIB_PATH		=		-L. libft/libft.a -lreadline -L/opt/homebrew/opt/readline/lib

NAME            =		minishell

.c.o:
				@$(CC) $(FLAGS) $(HEADERS) -c $< -o $(<:.c=.o)

$(NAME):        $(OBJS_EXEC)
				@make -C libft
				@$(CC) $(FLAGS) $(OBJS_EXEC) $(HEADERS) $(LIB_PATH) -o $(NAME)
				@echo "Makefile : minishell created"


all:            $(NAME)

clean:			
				@make clean -C libft
				@$(RM) $(OBJS_EXEC)
				@echo "Makefile : minishell objects removed"

fclean:         clean
				@make fclean -C libft
				@$(RM) $(NAME)
				@echo "Makefile : minishell removed"

re:             fclean all
