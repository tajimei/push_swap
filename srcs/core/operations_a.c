/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:16:58 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 20:37:26 by mtajima          ###   ########.fr       */
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

void	sa(t_state *state)
{
	t_node	*first;
	t_node	*second;

	if (!state->a->top || !state->a->top->next)
		return ;
	first = state->a->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	state->a->top = second;
	print_op(state, "sa", 2, OP_SA);
}

void	pa(t_state *state)
{
	t_node	*node;

	if (!state->b->top)
		return ;
	node = pop_node(state->b);
	push_node(state->a, node);
	print_op(state, "pa", 2, OP_PA);
}

void	ra(t_state *state)
{
	t_node	*first;
	t_node	*last;

	if (!state->a->top || !state->a->top->next)
		return ;
	first = state->a->top;
	state->a->top = first->next;
	first->next = NULL;
	last = state->a->top;
	while (last->next)
		last = last->next;
	last->next = first;
	print_op(state, "ra", 2, OP_RA);
}

void	rra(t_state *state)
{
	t_node	*cur;
	t_node	*prev;

	if (!state->a->top || !state->a->top->next)
		return ;
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
	print_op(state, "rra", 3, OP_RRA);
}
