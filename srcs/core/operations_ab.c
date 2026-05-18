#include "push_swap.h"

/* ========== 操作出力ヘルパー ========== */

static void	print_op(t_state *state, const char *op, int len, int idx)
{
	write(1, op, len);
	write(1, "\n", 1);
	state->op_count++;
	state->ops[idx]++;
}

/* ========== ss: saとsbを同時に実行 ========== */

void	ss(t_state *state)
{
	t_node	*first;
	t_node	*second;

	if (state->a->top && state->a->top->next)
	{
		first = state->a->top;
		second = first->next;
		first->next = second->next;
		second->next = first;
		state->a->top = second;
	}
	if (state->b->top && state->b->top->next)
	{
		first = state->b->top;
		second = first->next;
		first->next = second->next;
		second->next = first;
		state->b->top = second;
	}
	print_op(state, "ss", 2, OP_SS);
}

/* ========== rr: raとrbを同時に実行 ========== */

void	rr(t_state *state)
{
	t_node	*first;
	t_node	*last;

	if (state->a->top && state->a->top->next)
	{
		first = state->a->top;
		state->a->top = first->next;
		first->next = NULL;
		last = state->a->top;
		while (last->next)
			last = last->next;
		last->next = first;
	}
	if (state->b->top && state->b->top->next)
	{
		first = state->b->top;
		state->b->top = first->next;
		first->next = NULL;
		last = state->b->top;
		while (last->next)
			last = last->next;
		last->next = first;
	}
	print_op(state, "rr", 2, OP_RR);
}

/* ========== rrr: rraとrrbを同時に実行 ========== */

void	rrr(t_state *state)
{
	t_node	*cur;
	t_node	*prev;

	if (state->a->top && state->a->top->next)
	{
		prev = NULL;
		cur = state->a->top;
		while (cur->next)
		{
			prev = cur;
			cur = cur->next;
		}
		prev->next = NULL;
		cur->next = state->a->top;
		state->a->top = cur;
	}
	if (state->b->top && state->b->top->next)
	{
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
	}
	print_op(state, "rrr", 3, OP_RRR);
}
