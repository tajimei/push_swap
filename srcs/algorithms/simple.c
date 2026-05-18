#include "push_swap.h"

/*
** 選択ソート的アプローチ
** 「現在のaの最小値を探し、最小コストでaの先頭に持ってきてbにpush」を繰り返す
** 最後にbからpaで全部戻す
**
** コスト計算:
**   pos < size/2 → raをpos回
**   pos >= size/2 → rraを(size - pos)回
*/

/* ========== 最小値のポジション取得 ========== */

static int	min_position(t_stack *stack)
{
	t_node	*cur;
	int		min_val;
	int		min_pos;
	int		pos;

	cur = stack->top;
	min_val = cur->val;
	min_pos = 0;
	pos = 0;
	while (cur)
	{
		if (cur->val < min_val)
		{
			min_val = cur->val;
			min_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	return (min_pos);
}

/* ========== aの先頭にtarget_posを持ってくる ========== */

static void	rotate_to_top_a(t_state *state, int pos)
{
	int	size;
	int	i;

	size = state->a->size;
	if (pos <= size / 2)
	{
		i = 0;
		while (i < pos)
		{
			ra(state);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < size - pos)
		{
			rra(state);
			i++;
		}
	}
}

/* ========== bの先頭からaへ戻す（降順で積まれているので昇順になる） ========== */

static void	push_all_to_a(t_state *state)
{
	while (state->b->size > 0)
		pa(state);
}

/* ========== simple sort 本体 ========== */

/*
** 3要素以下は専用処理
** それ以上は選択ソートで全部bに積んでからaへ戻す
*/

static void	sort_three(t_state *state)
{
	int	a;
	int	b;
	int	c;

	a = state->a->top->val;
	b = state->a->top->next->val;
	c = state->a->top->next->next->val;
	if (a > b && b < c && a < c)
		sa(state);
	else if (a > b && b > c)
	{
		sa(state);
		rra(state);
	}
	else if (a > b && b < c && a > c)
		ra(state);
	else if (a < b && b > c && a < c)
	{
		sa(state);
		ra(state);
	}
	else if (a < b && b > c && a > c)
		rra(state);
}

static void	sort_two(t_state *state)
{
	if (state->a->top->val > state->a->top->next->val)
		sa(state);
}

void	sort_simple(t_state *state)
{
	int	pos;

	if (state->a->size <= 1)
		return ;
	if (state->a->size == 2)
	{
		sort_two(state);
		return ;
	}
	if (state->a->size == 3)
	{
		sort_three(state);
		return ;
	}
	while (state->a->size > 3)
	{
		pos = min_position(state->a);
		rotate_to_top_a(state, pos);
		pb(state);
	}
	sort_three(state);
	push_all_to_a(state);
}
