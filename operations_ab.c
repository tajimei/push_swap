/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_ab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:16:08 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 20:40:27 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_op(t_state *state, const char *op, int len, int idx)
{
	write(1, op, len);
	write(1, "\n", 1);
	state->op_count++;
	state->ops[idx]++;
}

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

static void	reverse_rotate_stack(t_stack *stack)
{
	t_node	*cur;
	t_node	*prev;

	if (!stack->top || !stack->top->next)
		return ;
	prev = NULL;
	cur = stack->top;
	while (cur->next)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = NULL;
	cur->next = stack->top;
	stack->top = cur;
}

void	rrr(t_state *state)
{
	reverse_rotate_stack(state->a);
	reverse_rotate_stack(state->b);
	print_op(state, "rrr", 3, OP_RRR);
}
