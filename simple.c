/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:35:33 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/23 14:04:29 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	min_position(t_stack *stack)
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

void	rotate_to_top_a(t_state *state, int pos)
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

void	push_all_to_a(t_state *state)
{
	while (state->b->size > 0)
		pa(state);
}

void	sort_three(t_state *state)
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

void	sort_two(t_state *state)
{
	if (state->a->top->val > state->a->top->next->val)
		sa(state);
}
