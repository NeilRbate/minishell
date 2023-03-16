GREEN = "\033[1;32m"
RED = "\033[1;31m"
YELLOW = "\033[1;33m"
BLUE = "\033[1;34m"
WHITE = "\033[1;37m"
RESET = "\033[0m"

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
									src/utils/pids.c \
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
							src/parsing/syntaxerror.c \
							src/parsing/redir3.c \
							src/parsing/file_gestion2.c \
							src/parsing/heredol.c

OBJS_EXEC       =		$(SRCS_EXEC:.c=.o) $(SRCS_PARS:.c=.o)

RM              =		rm -f

CC              =		cc

FLAGS           =		-Wall -Wextra -Werror -g

USER			=		$(shell whoami)

HEADERS			=		-I/Users/$(USER)/.brew/opt/readline/include -I include

LIB_PATH		=		-L. libft/libft.a -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

NAME            =		minishell

.c.o:
				@printf $(GREEN)"\r\033[KCreating object files 👉 "$(YELLOW)"<$<> "$(RESET)
				@$(CC) $(FLAGS) $(HEADERS) -c $< -o $(<:.c=.o)

$(NAME):        $(OBJS_EXEC)
				@make -C libft
				@$(CC) $(FLAGS) $(OBJS_EXEC) $(HEADERS) $(LIB_PATH) -o $(NAME)
				@printf $(GREEN)"\r\033[K✅ SUCCESS: "$(WHITE)$(NAME)$(GREEN)" has been created\n"$(RESET)


all:            $(NAME)

clean:			
				@make clean -C libft
				@$(RM) $(OBJS_EXEC)
				@printf $(RED)"\r\033[K➜ ["$(NAME)"] "$(WHITE)"clean"$(RED)" has been done\n"$(RESET)

fclean:         clean
				@make fclean -C libft
				@$(RM) $(NAME)
				@printf $(RED)"\r\033[K➜ ["$(NAME)"] "$(WHITE)"fclean"$(RED)" has been done\n"$(RESET)

re:             fclean all
