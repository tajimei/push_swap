NAME		= push_swap
BONUS_NAME	= checker

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDES	= -I includes/

# ========== ソースファイル ==========

CORE_SRCS	= srcs/core/stack_init.c \
			  srcs/core/operations_a.c \
			  srcs/core/operations_b.c \
			  srcs/core/operations_ab.c \
			  srcs/core/disorder.c

UTILS_SRCS	= srcs/utils/error.c \
			  srcs/utils/stack_utils.c \
			  srcs/utils/sort_utils.c \
			  srcs/utils/bench.c

ALGO_SRCS	= srcs/algorithms/simple.c \
			  srcs/algorithms/chunk.c \
			  srcs/algorithms/radix.c \
			  srcs/algorithms/adaptive.c

MAIN_SRC	= srcs/main.c

BONUS_SRCS	= srcs/bonus/checker_main.c \
			  srcs/bonus/checker_ops.c

SRCS		= $(CORE_SRCS) $(UTILS_SRCS) $(ALGO_SRCS) $(MAIN_SRC)

# ========== オブジェクトファイル ==========

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(CORE_SRCS:.c=.o) $(UTILS_SRCS:.c=.o) $(BONUS_SRCS:.c=.o)

# ========== ルール ==========

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
