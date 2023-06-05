NAME	= minishell
CFLAGS	= -Wall -Wextra -g -Werror
LIBFT	= libft
RL_LIB = -I /Users/$(USER)/.brew/opt/readline/include 
RL_LINK = -L /Users/$(USER)/.brew/opt/readline/lib 
HEADERS = -I $(LIBFT) -I ./includes $(RL_LIB)
LIBS = $(LIBFT)/libft.a
CC = gcc
#src/utils/errors.c						
SRCS	= 	src/loop_shell.c \
			src/minishell.c \
			src/env/get_env_value.c \
			src/env/remove_env_var.c \
			src/env/remove_exportenv_var.c \
			src/env/set_export_env_var.c \
			src/utils/init_data.c \
			src/utils/free.c \
			src/utils/signals.c \
			src/utils/pipes.c \
			src/utils/expand_variables.c \
			src/executer/exec_unset.c \
			src/executer/execute.c \
			src/executer/execute_utils.c \
			src/executer/parse_env.c \
			src/executer/exec_cd.c \
			src/executer/exec_pwd.c \
			src/executer/exec_env.c \
			src/executer/exec_echo.c \
			src/executer/exec_export.c \
			src/executer/exec_echo.c \
			src/parser/lexer/lexer.c \
			src/parser/lexer/utils.c \
			src/parser/lexer/actions.c \
			src/parser/lexer/states.c \
			src/parser/parser/parser.c \
			src/parser/parser/states.c \
			src/parser/parser/states2.c \
			src/parser/parser/actions.c \
			src/parser/parser/actions_heredoc.c \
			src/parser/parser/utils.c \

OBJS	= $(SRCS:.c=.o)

all: libft $(NAME)

libft:	
	make -C $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT)/libft.a -lreadline $(RL_LINK) $(HEADERS) -o $(NAME) 

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re libmlx libft