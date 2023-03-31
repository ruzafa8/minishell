SRCS			= get_next_line.c get_next_line_utils.c
BONUS_SRCS		= get_next_line_bonus.c get_next_line_bonus.c
BONUS_OBJS		= ${BONUS_SRCS:.c=.o}
OBJS			= ${SRCS:.c=.o}
NAME			= libnextline.a
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS} ${BONUS_OBJS}
	make -C ../ft
	cp ../ft/libft.a $(NAME) 
	ar -rcs ${NAME} ${BONUS_OBJS} ${OBJS}

clean:
	${RM} ${OBJS}
	${RM} ${BONUS_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
