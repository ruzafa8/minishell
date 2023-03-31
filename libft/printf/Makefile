SRCS		= ft_printf.c ft_print_format.c ft_print_ptr.c
SRCS_BONUS	= ft_printf_bonus.c ft_read_format_bonus.c ft_print_format_bonus.c\
			  ft_ctoa_bonus.c ft_ptoa_bonus.c ft_itoa_sized_bonus.c\
			  ft_basetoa_bonus.c ft_utils_bonus.c
OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}
NAME		= libftprintf.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I.
RM			= rm -f

all: $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS_BONUS}
	make -C ../get_next_line
	mv ../get_next_line/libnextline.a ${NAME}
	ar -rcs ${NAME} ${OBJS_BONUS}

clean:
	${RM} ${OBJS}
	${RM} ${OBJS_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
