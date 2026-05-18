#include "push_swap.h"

/* ========== 操作出力ヘルパー ========== */

static void	print_op(t_state *state, const char *op, int len, int idx)
{
	write(1, op, len);
	write(1, "\n", 1);
	state->op_count++;
	state->ops[idx]++;
}

/* ========== sb: スタックb先頭2要素を交換 ========== */

void	sb(t_state *state)
{
	t_node	*first;
	t_node	*second;

	if (!state->b->top || !state->b->top->next)
		return ;
	first = state->b->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	state->b->top = second;
	print_op(state, "sb", 2, OP_SB);
}

/* ========== pb: aの先頭をbの先頭へ ========== */

void	pb(t_state *state)
{
	t_node	*node;

	if (!state->a->top)
		return ;
	node = pop_node(state->a);
	push_node(state->b, node);
	print_op(state, "pb", 2, OP_PB);
}

/* ========== rb: スタックbを上方向に1回転 ========== */

void	rb(t_state *state)
{
	t_node	*first;
	t_node	*last;

	if (!state->b->top || !state->b->top->next)
		return ;
	first = state->b->top;
	state->b->top = first->next;
	first->next = NULL;
	last = state->b->top;
	while (last->next)
		last = last->next;
	last->next = first;
	print_op(state, "rb", 2, OP_RB);
}

/* ========== rrb: スタックbを下方向に1回転 ========== */

void	rrb(t_state *state)
{
	t_node	*cur;
	t_node	*prev;

	if (!state->b->top || !state->b->top->next)
		return ;
	prev = NULL;
	cur = state->b->top;
	while (cur->next)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = NULL;
	cur->next = state->b->top;
	state->b->top = cur;
	print_op(state, "rrb", 3, OP_RRB);
}
