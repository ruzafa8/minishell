OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}
NAME		= libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I.
RM			= rm -f

all: $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME):
	make -C printf
	mv printf/libftprintf.a ${NAME}

clean:
	make clean -C printf
	make clean -C ft
	make clean -C get_next_line

fclean: clean
	make fclean -C printf
	make fclean -C ft
	make fclean -C get_next_line
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
