#include "push_swap.h"

/* ========== 文字列→整数変換（エラー検出付き） ========== */

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
** 文字列が有効な整数か検証しながらint変換
** 無効 or INT範囲外 → error_exit
*/
static int	parse_int(const char *s, t_state *state)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!ft_isdigit(*s))
		error_exit(state);
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0');
		if (n * sign > 2147483647 || n * sign < -2147483648)
			error_exit(state);
		s++;
	}
	if (*s != '\0')
		error_exit(state);
	return ((int)(n * sign));
}

/* ========== 重複チェック ========== */

static void	check_duplicate(t_stack *a, int val, t_state *state)
{
	t_node	*cur;

	cur = a->top;
	while (cur)
	{
		if (cur->val == val)
			error_exit(state);
		cur = cur->next;
	}
}

/* ========== スタック確保 ========== */

static t_stack	*new_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->size = 0;
	return (stack);
}

/* ========== スタックに値を末尾追加（初期化用） ========== */

static void	push_back(t_stack *stack, int val, t_state *state)
{
	t_node	*node;
	t_node	*cur;

	node = new_node(val);
	if (!node)
		error_exit(state);
	if (!stack->top)
	{
		stack->top = node;
	}
	else
	{
		cur = stack->top;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
	stack->size++;
}

/* ========== state解放 ========== */

static void	free_stack(t_stack *stack)
{
	t_node	*cur;
	t_node	*next;

	if (!stack)
		return ;
	cur = stack->top;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(stack);
}

void	free_state(t_state *state)
{
	if (!state)
		return ;
	free_stack(state->a);
	free_stack(state->b);
	free(state);
}

/* ========== メイン初期化 ========== */

/*
** argc/argv からスタックaを構築する
** "--simple" "--medium" 等のフラグは呼び出し元で除去済みを想定
*/
t_state	*init_state(int argc, char **argv, int bench_mode)
{
	t_state	*state;
	int		i;
	int		val;

	if (argc < 1)
		return (NULL);
	state = malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	state->op_count = 0;
	state->bench_mode = bench_mode;
	state->disorder = 0.0;
	i = 0;
	while (i < 11)
		state->ops[i++] = 0;
	state->a = new_stack();
	state->b = new_stack();
	if (!state->a || !state->b)
		error_exit(state);
	i = 0;
	while (i < argc)
	{
		val = parse_int(argv[i], state);
		check_duplicate(state->a, val, state);
		push_back(state->a, val, state);
		i++;
	}
	return (state);
}
