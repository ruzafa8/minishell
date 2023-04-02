NAME	= minishell
CFLAGS	= -Wall -Wextra -g -Werror
LIBFT	= libft
HEADERS = -I $(LIBFT) -I ./includes
LIBS = $(LIBFT)/libft.a
SRCS	= 	src/loop_shell.c \
			src/minishell.c \
			src/env/get_env_value.c \
			src/executer/execute.c \
			src/executer/parse_env.c \
			src/executer/exec_cd.c \
			src/executer/exec_pwd.c \
			src/parser/parser.c \
			src/parser/command_nodes.c\
			src/parser/generic_nodes.c\
			src/parser/cd_nodes.c\
			src/parser/pwd_nodes.c

OBJS	= $(SRCS:.c=.o)

all: libft $(NAME)

libft:	
	make -C $(LIBFT)

%.o: %.c
	gcc $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(SRCS) $(LIBFT)/libft.a $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re libmlx libft