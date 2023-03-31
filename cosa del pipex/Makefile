SRCS		= src/main.c src/parse_env.c src/check_access.c \
			  src/exec.c src/utils.c
OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}
NAME		= pipex
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I.
RM			= rm -f

all: $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

libft.a:
	make -C ./libft
	cp libft/libft.a libft.a

$(NAME): libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lft -L.

clean:
	make clean -C ./libft
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(RM) main.o checker.o

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME) checker
	$(RM) libft.a

re: fclean all

.PHONY: all clean fclean re bonus check
