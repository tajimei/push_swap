NAME		= push_swap

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDES	= -I includes/

CORE_SRCS	= stack_init.c \
			  stack_init2.c \
			  operations_a.c \
			  operations_b.c \
			  operations_ab.c \
			  disorder.c

UTILS_SRCS	= error.c \
			  stack_utils.c \
			  stack_utils2.c \
			  str_utils.c \
			  sort_utils.c \
			  bench.c

ALGO_SRCS	= simple.c \
			  simple2.c \
			  chunk.c \
			  chunk2.c \
			  radix.c \
			  adaptive.c

MAIN_SRC	= main.c

SRCS		= $(CORE_SRCS) $(UTILS_SRCS) $(ALGO_SRCS) $(MAIN_SRC)

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
